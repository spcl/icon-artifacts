export _RELEASE=1

unset _PERMUTE_DIMS

export GENCODE_NUMBER=90

export _PERMUTE_DIMS=1

python -m utils.stages.compile_gpu_stage8

export _PERMUTE_DIMS=0

python -m utils.stages.compile_gpu_stage8
