# Source f2dace
#!/bin/bash
export RELEASE=FALSE
export _USE_NVHPC=FALSE
export _USE_CUDA_EVENTS=FALSE

source .f2dace/bin/activate

python -m utils.stages.compile_gpu_stage5
./velocity_gpu.stage5 1>stage5_dimadd_jul1.out 2>stage5_dimadd_jul1.err
python utils/compare_got_and_want.py 1>stage5_dimadd_jul1.compare.out 2>stage5_dimadd_jul1.compare.err

python -m utils.stages.compile_gpu_stage6
./velocity_gpu.stage6 1>stage6_dimadd_jul1.out 2>stage6_dimadd_jul1.err
python utils/compare_got_and_want.py 1>stage6_dimadd_jul1.compare.out 2>stage6_dimadd_jul1.compare.err

python -m utils.stages.compile_gpu_stage7
./velocity_gpu.stage7 1>stage7_dimadd_jul1.out 2>stage7_dimadd_jul1.err
python utils/compare_got_and_want.py 1>stage7_dimadd_jul1.compare.out 2>stage7_dimadd_jul1.compare.err