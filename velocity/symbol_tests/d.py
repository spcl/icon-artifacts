import dace

D0 = dace.symbol('D0')
D1 = dace.symbol('D1')
D2 = dace.symbol('D2')

@dace.program
def kernel(A: dace.float64[D0, D1, D2]):
    for i, j, k in dace.map[0:4, 0:D1, 0:D2]:
        A[i, j, k] = A[i, j, k] + 1.0

sdfg = kernel.to_sdfg()
sdfg.save("original.sdfg")

sdfg.compile()