from dace import SDFG
from dace.transformation.interstate import LoopToMap

'''
g = SDFG.from_file("cloudsc-simplified.sdfgz")
g.apply_transformations_repeated(LoopToMap)
g.save("cloudsc-simplified-loop2map.sdfgz", compress=True)
exit()
'''

g = SDFG.from_file("cloudsc-simplified.sdfgz")
g.build_folder = "./cloudsc-simplified-codegen"
g.compile()

g = SDFG.from_file("cloudsc-simplified-loop2map.sdfgz")
g.build_folder = "./cloudsc-simplified-loop2map-codegen"
g.compile()
