import ast
import dace
import re
from typing import Set, Callable

from dace.codegen.control_flow import ConditionalBlock
from dace.sdfg.sdfg import CodeBlock

def _strip_suffix_if_matches(s: str) -> str:
    match = re.search(r'_s_\d+$', s)
    if match:
        return s[:match.start()]
    return s

def _array_same(a_name1: str, a_name2: str, array1: dace.data.Array, array2: dace.data.Array) -> bool:
    if a_name1 != a_name2:
        return False
    if array1.dtype != array2.dtype:
        return False
    if array1.shape != array2.shape:
        return False
    if array1.transient != array2.transient:
        return False
    if array1.storage != array2.storage:
        return False
    return True

def _scalar_same(a_name1: str, a_name2: str, scalar1: dace.data.Scalar, scalar2: dace.data.Scalar) -> bool:
    if a_name1 != a_name2:
        return False
    if scalar1.dtype != scalar2.dtype:
        return False
    if scalar1.transient != scalar2.transient:
        return False
    if scalar1.storage != scalar2.storage:
        return False
    return True

def _container_array_same(a_name1: str, a_name2: str, ca1: dace.data.ContainerArray, ca2: dace.data.ContainerArray) -> bool:
    if a_name1 != a_name2:
        return False
    if ca1.shape != ca2.shape:
        return False
    if ca1.dtype != ca2.dtype:
        return False
    assert isinstance(ca1, dace.data.Structure)
    assert isinstance(ca2, dace.data.Structure)
    s1: dace.data.Structure = ca1.stype
    s2: dace.data.Structure = ca2.stype
    same = _struct_same(s1.name, s2.name, s1, s2)
    return same

def _struct_same(s_name1: str, s_name2: str, struct1: dace.data.Structure, struct2: dace.data.Structure) -> bool:
    if s_name1 != s_name2:
        return False
    if struct1.dtype != struct2.dtype:
        return False
    if struct1.shape != struct2.shape:
        return False
    for member_name, member in struct1.members.items():
        if member_name not in struct2.members:
            return False
        member2 = struct2.members[member_name]
        if type(member) != type(member2):
            return False
        if isinstance(member, dace.data.Array):
            same = _array_same(member_name, member_name, member, member2)
            if not same:
                return False
        elif isinstance(member, dace.data.Scalar):
            same = _scalar_same(member_name, member_name, member, member2)
            if not same:
                return False
        elif isinstance(member, dace.data.Structure):
            same = _struct_same(member_name, member_name, member, member2)
            if not same:
                return False
        elif isinstance(member, dace.data.ContainerArray):
            same = _container_array_same(member_name, member_name, member, member2)
            if not same:
                return False
    return True

def _symbols_same(s1: Set[str], s2: Set[str]) -> bool:
    if len(s1) != len(s2):
        return False
    for sym in s1:
        if sym not in s2:
            return False
    return True

def _prune_name_of_structs(sdfg: dace.SDFG) -> None:
    pass

def _print_names(name: str, struct: dace.data.Structure, depth: int) -> None:
    indent = '  ' * depth
    print(f"{indent}Name: {name}, Type: {struct.name}")
    for member_name, member in struct.members.items():
        if isinstance(member, dace.data.Structure):
            _print_names(member_name, member, depth + 1)
        elif isinstance(member, dace.data.ContainerArray):
            print(f"{indent}  Member Container Array: {member_name}")
            _print_names(member_name, member.stype, depth + 1)
        else:
            print(f"{indent}  Member: {member_name}, Type: {member.dtype}, Transient: {member.transient}, Storage: {member.storage}")

def _repl_struct_names(name: str, struct: dace.data.Structure, depth: int) -> None:
    indent = '  ' * depth
    _new_members = dict()
    for member_name, member in struct.members.items():
        new_member_name = _strip_suffix_if_matches(member_name)
        print(f"{indent}Name (From) {member_name} => (TO) {new_member_name}")
        _new_members[new_member_name] = member
    struct.members = _new_members

    for member_name, member in struct.members.items():
        if isinstance(member, dace.data.Structure):
            _repl_struct_names(member_name, member, depth + 1)
        elif isinstance(member, dace.data.ContainerArray):
            _repl_struct_names(member_name, member.stype, depth + 1)


def _rename_on_if_conds(sdfg: dace.SDFG, src: str, dst: str, recursive=False):
    gpu_host_name_map = {src: dst}

    for _, node in enumerate(sdfg.nodes()) if not recursive else sdfg.all_nodes_recursive():
        if not isinstance(node, ConditionalBlock):
            continue

        for b in node.branches:
            if b[0] is None:
                continue
            if isinstance(b[0].code, list):
                for i, el in enumerate(b[0].code):
                    if isinstance(el, str):
                        for src,dst in gpu_host_name_map.items():
                            b[0].code[i] = b[0].code[i].replace(src,dst)
                    else:
                        def replace_x_with_y(expr: ast.Expr, repl_dict) -> ast.Expr:
                            expr_str = ast.unparse(expr).strip()
                            for src, dst in repl_dict.items():
                                modified_str = expr_str.replace(src, dst)
                            return ast.parse(modified_str, mode="eval").body
                        b[0].code[i] = replace_x_with_y(b[0].code[i], gpu_host_name_map)
            else:
                assert isinstance(b[0].code, str)
                for src,dst in gpu_host_name_map.items():
                    b[0].code = b[0].code.replace(src, dst)

def _rename_symbols(sdfg: dace.SDFG, check_func: Callable) -> None:
    # Build the symbol mapping
    new_symbols = {}
    for sym_name in sdfg.symbols:
        new_sym = check_func(sym_name)
        if new_sym != sym_name:
            new_symbols[sym_name] = new_sym

    # Ensure replaced on ifs
    sdfg.replace_dict(repldict=new_symbols)
    for old_s, new_s in new_symbols.items():
        _rename_on_if_conds(sdfg, old_s, new_s, False)

    # Go to Nested SDFGs, also fix the symbol mapping
    for state in sdfg.all_states():
        for node in state.nodes():
            if isinstance(node, dace.nodes.NestedSDFG):
                node.symbol_mapping = {
                    check_func(k): check_func(v) for k, v in node.symbol_mapping.items()
                }

            if isinstance(node, dace.nodes.NestedSDFG):
                _rename_symbols(node.sdfg, check_func)

    new_global_code = dict()
    new_init_code = dict()
    for old_s, new_s in new_symbols.items():
        for k, v in sdfg.global_code.items():
            new_global_code[k.replace(old_s, new_s)] = CodeBlock(v.as_string.replace(old_s, new_s), language=dace.dtypes.Language.CPP) if isinstance(v, CodeBlock) else CodeBlock(v.replace(old_s, new_s), language=dace.dtypes.Language.CPP)
        for k, v in sdfg.init_code.items():
            new_init_code[k.replace(old_s, new_s)] = CodeBlock(v.as_string.replace(old_s, new_s), language=dace.dtypes.Language.CPP) if isinstance(v, CodeBlock) else CodeBlock(v.replace(old_s, new_s), language=dace.dtypes.Language.CPP)

    sdfg.init_code = new_init_code
    sdfg.global_code = new_global_code


def prune_names(sdfg: dace.SDFG) -> None:
    cname = "p_int"
    for arr_name, arr in sdfg.arrays.items():
        if arr_name == cname:
            _print_names(arr_name, arr, 0)

        if isinstance(arr, dace.data.Structure):
            _repl_struct_names(arr_name, arr, 0)

        if arr_name == cname:
            _print_names(arr_name, arr, 0)

    _rename_symbols(sdfg, _strip_suffix_if_matches)

    #sdfg.save("before_prune.sdfgz", compress=True)
    sdfg.validate()
    #raise Exception("UWU")
