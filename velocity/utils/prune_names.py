import dace
import re
from typing import Set

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

def prune_names(sdfg: dace.SDFG) -> None:
    pass