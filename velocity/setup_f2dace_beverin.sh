export ROCM_HOME=/opt/rocm
export HIP_PATH=$ROCM_HOME
export HIPCC=$ROCM_HOME/bin/hipcc
export PATH=$ROCM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$ROCM_HOME/lib:$ROCM_HOME/lib64:$LD_LIBRARY_PATH
export CPATH=$ROCM_HOME/include:$CPATH
export LIBRARY_PATH=$ROCM_HOME/lib:$ROCM_HOME/lib64:$LIBRARY_PATH
export CFLAGS="-I$ROCM_HOME/include"
export LDFLAGS="-L$ROCM_HOME/lib -L$ROCM_HOME/lib64"
export CUPY_INSTALL_USE_HIP=1
export HCC_AMDGPU_TARGET=gfx942

spack load python@3.13.8
export CFLAGS="-I$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))") ${CFLAGS}"
export C_INCLUDE_PATH="$(python3.13 -c "import sysconfig; print(sysconfig.get_path('include'))"):${C_INCLUDE_PATH}"

export HCC_AMDGPU_TARGET=gfx942
export CUPY_HIPCC_GENERATE_CODE=--offload-arch=gfx942

START_DIR=$(pwd)
DACE_DIR=$(python3 -c "import dace; import os; print(os.path.dirname(os.path.dirname(dace.__file__)))")
echo "dace found at: $DACE_DIR"
cd "$DACE_DIR"
git fetch origin
git checkout f2dace/staging
cd "$START_DIR"