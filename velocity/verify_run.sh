# Source f2dace
#!/bin/bash
export _RELEASE=FALSE
export _USE_NVHPC=FALSE
export _USE_CUDA_EVENTS=FALSE

source .f2dace/bin/activate

for s in {7..7}; do
    echo "Running Stage ${s}..."
    python -m utils.stages.compile_gpu_stage${s}
    ./velocity_gpu.stage${s} 1>stage${s}_dimadd_jul1.out 2>stage${s}_dimadd_jul1.err
    python utils/compare_got_and_want.py -r ./gotwant/data_nproma20480 1>stage${s}_dimadd_jul1.compare.out 2>stage${s}_dimadd_jul1.compare.err
done