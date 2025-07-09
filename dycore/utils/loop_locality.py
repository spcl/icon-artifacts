import dace
from dace.sdfg.state import LoopRegion, ConditionalBlock
from utils import find_node_by_name


def make_array_loop_local(sdfg: dace.SDFG, array_name, loop_name):
    """
    Renames an array in the loop, so it's only accessed in the loop. You need to make sure that the array is not accessed outside of the loop (or written before read outside of the loop).
    """
    # Find the loop
    loop, _ = find_node_by_name(sdfg, loop_name)

    # Creat a new array
    array = sdfg.arrays[array_name]
    if isinstance(array, dace.data.Scalar):
        new_name, _ = sdfg.add_scalar(
            f"{array_name}_local",
            dtype=array.dtype,
            storage=array.storage,
            transient=array.transient,
            lifetime=array.lifetime,
            debuginfo=array.debuginfo,
            find_new_name=True,
        )
    else:
        new_name, _ = sdfg.add_array(
            f"{array_name}_local",
            shape=array.shape,
            dtype=array.dtype,
            storage=array.storage,
            location=array.location,
            transient=array.transient,
            strides=array.strides,
            offset=array.offset,
            lifetime=array.lifetime,
            debuginfo=array.debuginfo,
            allow_conflicts=array.allow_conflicts,
            total_size=array.total_size,
            find_new_name=True,
            alignment=array.alignment,
            may_alias=array.may_alias,
        )

    # Replace each occurrence of the array in the loop
    loop.replace(array_name, new_name)
    nodelist = list(loop.nodes())
    while nodelist:
        node = nodelist.pop()
        if isinstance(node, (LoopRegion, ConditionalBlock)):
            nodelist.extend(node.nodes())
            node.replace_meta_accesses({array_name: new_name})


def apply_loop_locality_pass(sdfg: dace.SDFG):
    if "nproma32" in sdfg.name:
        try:
            make_array_loop_local(sdfg, "difcoef", "FOR_l_505_c_505")
        except Exception as e:
            print("Make Array Loop Local failed for difcoef, For_l505_c_505:", e)
        try:
            make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_555_c_555")
        except Exception as e:
            print("Make Array Loop Local failed for _if_cond_27, For_l555_c_555:", e)
    elif "nproma20480" in sdfg.name:
        try:
            make_array_loop_local(sdfg, "difcoef", "FOR_l_589_c_589")
        except Exception as e:
            print("Make Array Loop Local failed for difcoef, FOR_l_589_c_589:", e)
        try:
            make_array_loop_local(sdfg, "_if_cond_27", "FOR_l_555_c_555")
        except Exception as e:
            print("Make Array Loop Local failed for _if_cond_27, FOR_l_639_c_639:", e)

    else:
        raise ValueError("Unknown NPROMA size")
