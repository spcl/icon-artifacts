from dace import SDFG, DeviceType
from dace.transformation.auto import auto_optimize as aopt
from dace.transformation.interstate import LoopToMap

'''
g = SDFG.from_file("cloudsc.sdfg")
g.build_folder = "./cloudsc-codegen"
g.compile()
g.simplify()
g.save('cloudsc-simplified.sdfg')
g.build_folder = './cloudsc-simplified-codegen'
g.compile()
exit()
'''

g = SDFG.from_file("cloudsc-simplified.sdfg")
aopt.auto_optimize(g, DeviceType.CPU)
g.save('cloudsc-simplified-aopt.sdfg')
g.build_folder = './cloudsc-simplified-aopt-codegen'
g.compile()
exit()

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
