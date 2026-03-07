import numpy as np
from pathlib import Path
from typing import Union, Optional
import re
import glob

# ── parsing helpers ──

def _peek_line(lines, pos):
    while pos < len(lines) and lines[pos].strip() == '':
        pos += 1
    return (lines[pos].strip(), pos) if pos < len(lines) else (None, pos)

def _read_line(lines, pos):
    while pos < len(lines) and lines[pos].strip() == '':
        pos += 1
    assert pos < len(lines), f"unexpected EOF at line {pos}"
    return lines[pos].strip(), pos + 1

def _expect(lines, pos, substr):
    line, pos = _read_line(lines, pos)
    assert substr in line, f"expected '{substr}', got '{line}' at line {pos-1}"
    return pos

def _read_scalar(lines, pos, dtype=float):
    val, pos = _read_line(lines, pos)
    return dtype(val), pos

def _read_array_meta(lines, pos):
    pos = _expect(lines, pos, '# rank')
    rank, pos = _read_scalar(lines, pos, int)
    pos = _expect(lines, pos, '# size')
    shape = []
    for _ in range(rank):
        s, pos = _read_scalar(lines, pos, int)
        shape.append(s)
    pos = _expect(lines, pos, '# lbound')
    lbound = []
    for _ in range(rank):
        lb, pos = _read_scalar(lines, pos, int)
        lbound.append(lb)
    return shape, lbound, pos

def _read_array(lines, pos, dtype=np.float64):
    shape, lbound, pos = _read_array_meta(lines, pos)
    pos = _expect(lines, pos, '# entries')
    n = int(np.prod(shape))
    vals = []
    for _ in range(n):
        v, pos = _read_scalar(lines, pos, dtype)
        vals.append(v)
    arr = np.array(vals, dtype=dtype).reshape(shape, order='F')
    arr = np.ascontiguousarray(arr.T)
    shape_reversed = list(reversed(shape))
    lbound_reversed = list(reversed(lbound))
    return arr, shape_reversed, lbound_reversed, pos

def _read_alloc_field(lines, pos, dtype=np.float64):
    pos = _expect(lines, pos, '# alloc')
    allocated, pos = _read_scalar(lines, pos, int)
    if allocated:
        return _read_array(lines, pos, dtype)
    return None, None, None, pos

def _read_assoc_field(lines, pos, dtype=np.float64):
    pos = _expect(lines, pos, '# assoc')
    associated, pos = _read_scalar(lines, pos, int)
    if associated:
        pos = _expect(lines, pos, '# missing')
        _missing, pos = _read_scalar(lines, pos, int)
        return _read_array(lines, pos, dtype)
    return None, None, None, pos


# ── schema ──

SCHEMA = {
    'global_data': [
        ('nflatlev',                   'array',  np.int32),
        ('i_am_accel_node',            'scalar', int),
        ('lextra_diffu',               'scalar', int),
        ('nproma',                     'scalar', int),
        ('timers_level',               'scalar', int),
        ('timer_solve_nh_veltend',     'scalar', int),
        ('timer_intp',                 'scalar', int),
        ('nrdmax',                     'array',  np.int32),
    ],
    't_patch': [
        ('nblks_c',      'scalar', int),
        ('nblks_e',      'scalar', int),
        ('nblks_v',      'scalar', int),
        ('cells',        'struct', 't_grid_cells'),
        ('edges',        'struct', 't_grid_edges'),
        ('verts',        'struct', 't_grid_vertices'),
    ],
    't_grid_cells': [
        ('neighbor_idx', 'alloc', np.int32),
        ('neighbor_blk', 'alloc', np.int32),
        ('edge_idx',     'alloc', np.int32),
        ('edge_blk',     'alloc', np.int32),
        ('area',         'assoc', np.float64),
        ('start_index',  'alloc', np.int32),
        ('end_index',    'alloc', np.int32),
        ('start_block',  'alloc', np.int32),
        ('end_block',    'alloc', np.int32),
        ('decomp_info',  'struct', 't_grid_domain_decomp_info'),
    ],
    't_grid_domain_decomp_info': [
        ('owner_mask', 'alloc', np.int32),
    ],
    't_grid_edges': [
        ('cell_idx',              'alloc', np.int32),
        ('cell_blk',              'alloc', np.int32),
        ('vertex_idx',            'alloc', np.int32),
        ('vertex_blk',            'alloc', np.int32),
        ('tangent_orientation',   'alloc', np.float64),
        ('quad_idx',              'alloc', np.int32),
        ('quad_blk',              'alloc', np.int32),
        ('inv_primal_edge_length','alloc', np.float64),
        ('inv_dual_edge_length',  'alloc', np.float64),
        ('area_edge',             'alloc', np.float64),
        ('f_e',                   'alloc', np.float64),
        ('fn_e',                  'alloc', np.float64),
        ('ft_e',                  'alloc', np.float64),
        ('start_index',           'alloc', np.int32),
        ('end_index',             'alloc', np.int32),
        ('start_block',           'alloc', np.int32),
        ('end_block',             'alloc', np.int32),
    ],
    't_grid_vertices': [
        ('cell_idx',    'alloc', np.int32),
        ('cell_blk',    'alloc', np.int32),
        ('edge_idx',    'alloc', np.int32),
        ('edge_blk',    'alloc', np.int32),
        ('start_index', 'alloc', np.int32),
        ('end_index',   'alloc', np.int32),
        ('start_block', 'alloc', np.int32),
        ('end_block',   'alloc', np.int32),
    ],
    't_nh_prog': [
        ('w',  'assoc', np.float64),
        ('vn', 'assoc', np.float64),
    ],
    't_nh_diag': [
        ('vt',            'assoc', np.float64),
        ('vn_ie',         'assoc', np.float64),
        ('w_concorr_c',   'assoc', np.float64),
        ('ddt_vn_apc_pc', 'assoc', np.float64),
        ('ddt_w_adv_pc',  'assoc', np.float64),
        ('max_vcfl_dyn',  'scalar', float),
    ],
    't_nh_metrics': [
        ('ddxn_z_full',       'assoc', np.float64),
        ('ddxt_z_full',       'assoc', np.float64),
        ('ddqz_z_full_e',    'assoc', np.float64),
        ('ddqz_z_half',      'assoc', np.float64),
        ('wgtfac_c',         'assoc', np.float64),
        ('wgtfac_e',         'assoc', np.float64),
        ('wgtfacq_e',        'assoc', np.float64),
        ('coeff_gradekin',   'assoc', np.float64),
        ('coeff1_dwdz',      'assoc', np.float64),
        ('coeff2_dwdz',      'assoc', np.float64),
        ('deepatmo_gradh_mc','assoc', np.float64),
        ('deepatmo_invr_mc', 'assoc', np.float64),
        ('deepatmo_gradh_ifc','assoc', np.float64),
        ('deepatmo_invr_ifc','assoc', np.float64),
    ],
    't_int_state': [
        ('c_lin_e',         'alloc', np.float64),
        ('e_bln_c_s',       'alloc', np.float64),
        ('cells_aw_verts',  'alloc', np.float64),
        ('rbf_vec_coeff_e', 'alloc', np.float64),
        ('geofac_grdiv',    'alloc', np.float64),
        ('geofac_rot',      'alloc', np.float64),
        ('geofac_n2s',      'alloc', np.float64),
    ],
}


def parse_struct(lines, pos, struct_type, prefix=''):
    result = {}
    schema = SCHEMA[struct_type]
    for field_name, kind, dtype in schema:
        fqn = f"{prefix}.{field_name}" if prefix else field_name
        if kind == 'array':
            pos = _expect(lines, pos, f'# {field_name}')
            arr, shape, lbound, pos = _read_array(lines, pos, dtype)
            result[fqn] = {'data': arr, 'shape': shape, 'lbound': lbound}
        elif kind == 'scalar':
            pos = _expect(lines, pos, f'# {field_name}')
            val, pos = _read_scalar(lines, pos, dtype)
            result[fqn] = {'data': val, 'shape': [], 'lbound': []}
        elif kind == 'alloc':
            pos = _expect(lines, pos, f'# {field_name}')
            arr, shape, lbound, pos = _read_alloc_field(lines, pos, dtype)
            if arr is not None:
                result[fqn] = {'data': arr, 'shape': shape, 'lbound': lbound}
        elif kind == 'assoc':
            pos = _expect(lines, pos, f'# {field_name}')
            arr, shape, lbound, pos = _read_assoc_field(lines, pos, dtype)
            if arr is not None:
                result[fqn] = {'data': arr, 'shape': shape, 'lbound': lbound}
        elif kind == 'struct':
            pos = _expect(lines, pos, f'# {field_name}')
            sub, pos = parse_struct(lines, pos, dtype, prefix=fqn)
            result.update(sub)
    return result, pos


def load_serde_file(path: Union[str, Path], struct_type: str):
    path = Path(path)
    lines = path.read_text().splitlines()
    result, _ = parse_struct(lines, 0, struct_type)
    return result


def load_bare_array(path: Union[str, Path], dtype=np.float64):
    """Load a file that contains a single bare array (rank/size/lbound/entries)."""
    path = Path(path)
    lines = path.read_text().splitlines()
    arr, shape, lbound, _ = _read_array(lines, 0, dtype)
    return arr, shape, lbound


# ── filename → struct type / bare array mapping ──

FILE_PREFIX_TO_STRUCT = {
    'p_patch':      't_patch',
    'p_prog':       't_nh_prog',
    'p_diag':       't_nh_diag',
    'p_metrics':    't_nh_metrics',
    'p_int_state':  't_int_state',
    'global_data':  'global_data',
    # Legacy names (in case both conventions appear)
    'p_nh_prog':    't_nh_prog',
    'p_nh_diag':    't_nh_diag',
    'p_nh_metrics': 't_nh_metrics',
}

# Bare array files: prefix → dtype
BARE_ARRAY_FILES = {
    'z_kin_hor_e':      np.float64,
    'z_vt_ie':          np.float64,
    'z_w_concorr_me':   np.float64,
}

_FILE_RE = re.compile(r'^(.+)\.t([01])\.(\d+)\.data$')


def _flatten_key(dotted_name: str) -> str:
    """verts.end_block → verts_end_block"""
    return dotted_name.replace('.', '_')


def load_folder(folder: Union[str, Path], timestep: int) -> dict:
    """Load all serde files for a given timestep from folder.

    Returns a flat dict where:
      - t0 fields        → key = flattened name,          e.g. 'verts_end_block'
      - t1 fields        → key = flattened name + '_ref',  e.g. 'verts_end_block_ref'
      - bare array t0    → key = filename prefix,          e.g. 'z_kin_hor_e'
      - bare array t1    → key = filename prefix + '_ref', e.g. 'z_kin_hor_e_ref'
      - scalars           → bare python value
      - arrays            → numpy array (C-order, reversed dims)

    Parameters
    ----------
    folder : path to directory containing the .data serde files
    timestep : integer timestep, e.g. 1 matches .1.data, 9 matches .9.data
    """
    folder = Path(folder)
    result = {}

    for fpath in sorted(folder.glob(f'*.t[01].{timestep}.data')):
        m = _FILE_RE.match(fpath.name)
        if not m:
            print(f"  [skip] no regex match: {fpath.name}")
            continue
        base_name = m.group(1)
        t_tag = int(m.group(2))
        step_str = m.group(3)
        if int(step_str) != timestep:
            continue

        is_ref = (t_tag == 1)
        tag_str = 'ref (t1)' if is_ref else 'input (t0)'

        # ── Try as struct file first ──
        struct_type = FILE_PREFIX_TO_STRUCT.get(base_name)
        if struct_type is not None:
            print(f"  {fpath.name:40s} → {struct_type:20s} [{tag_str}]")
            parsed = load_serde_file(fpath, struct_type)
            for dotted_name, info in parsed.items():
                flat = _flatten_key(dotted_name)
                if is_ref:
                    flat += '_ref'
                if flat in result:
                    print(f"    [warn] duplicate key '{flat}', overwriting")
                result[flat] = info['data']
            continue

        # ── Try as bare array file ──
        bare_dtype = BARE_ARRAY_FILES.get(base_name)
        if bare_dtype is not None:
            print(f"  {fpath.name:40s} → bare array             [{tag_str}]")
            arr, shape, lbound = load_bare_array(fpath, bare_dtype)
            key = base_name + ('_ref' if is_ref else '')
            if key in result:
                print(f"    [warn] duplicate key '{key}', overwriting")
            result[key] = arr
            continue

        # ── Unknown: try as bare float64 array as fallback ──
        print(f"  {fpath.name:40s} → bare array (auto)      [{tag_str}]")
        try:
            arr, shape, lbound = load_bare_array(fpath, np.float64)
            key = base_name + ('_ref' if is_ref else '')
            result[key] = arr
        except Exception as e:
            print(f"    [error] failed to parse {fpath.name}: {e}")

    return result


def print_result(data: dict):
    scalars, arrays = [], []
    for k, v in sorted(data.items()):
        (arrays if isinstance(v, np.ndarray) else scalars).append((k, v))
    if scalars:
        print("\n  Scalars:")
        for k, v in scalars:
            print(f"    {k:50s} = {v}")
    if arrays:
        print("\n  Arrays:")
        for k, v in arrays:
            print(f"    {k:50s}  shape={str(v.shape):20s}  dtype={v.dtype}")


if __name__ == '__main__':
    import sys
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <folder> <timestep>")
        print(f"  Example: {sys.argv[0]} ./serde_out 9")
        sys.exit(1)

    folder = sys.argv[1]
    timestep = int(sys.argv[2])

    print(f"Loading timestep {timestep} from {folder}/\n")
    data = load_folder(folder, timestep)
    print_result(data)