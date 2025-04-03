from dace import SDFG

g = SDFG.from_file("cloudsc-simplified.sdfgz")
g.build_folder = "./cloudsc-simplified-codegen"
g.compile()

g = SDFG.from_file("cloudsc-simplified-loop2map.sdfgz")
g.build_folder = "./cloudsc-simplified-loop2map-codegen"
g.compile()
