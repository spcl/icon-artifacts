from pathlib import Path
import shutil
import dace
import os

from dace.transformation.interstate import ContinueToCondition, LoopToMap
from dace.transformation.passes import StructToContainerGroups, SymbolPropagation, ConstantPropagation

from utils import *

sdfg = dace.SDFG.from_file("solve_nh_predictor_post.sdfgz")

count_loops(sdfg, verbose=False, use_assert=True)

sdfg.apply_transformations_repeated(ContinueToCondition)
StructToContainerGroups(
        validate=False,
        save_steps=False,
        verbose=False,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=False,
        clean_trivial_views=True,
        shallow_copy=False,
        shallow_copy_to_gpu=False,
        taskloop = False,
    ).apply_pass(sdfg, {})
sdfg.simplify(skip=["ArrayElimination"])
SymbolPropagation().apply_pass(sdfg, {})
sdfg.simplify(skip=["ArrayElimination"]) 
ConstantPropagation().apply_pass(sdfg, {})

sdfg.apply_transformations_repeated(LoopToMap, permissive=True)
count_loops(sdfg, verbose=True, use_assert=True)

sdfg.save("out.sdfgz", compress=True)


# Loops that cannot be transformed to maps:
# FOR_l_1503_c_1503: Write to array independent of loop index. Not a map due to potential data race. But outer loop can be eliminated, as that array is the only one written to and it's not read from.

# FOR_l_1271_c_1271: Same as above. But somehow the inner maps output writes the whole array. Seeming independent of the outer loop.

# FOR_l_1315_c_1315: Same as above, but this time the read is independent, whereas the write is not. Thus there is RAW dependency.

# FOR_l_1320_c_1320: Same as FOR_l_1503_c_1503.
# FOR_l_1424_c_1424: Same as FOR_l_1271_c_1271. But has RAW.
# FOR_l_1430_c_1430: Same as FOR_l_1271_c_1271. But has RAW.
# FOR_l_1451_c_1451: Same as FOR_l_1503_c_1503.
# FOR_l_1458_c_1458: Same as FOR_l_1503_c_1503.
