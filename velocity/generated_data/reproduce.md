# Generate SDFG and Data

The branches and commits used to generate the data are:
[icon-dace](https://github.com/spcl/icon-dace), branch: `pratyai/working-patches-2024.10` => commit hash: `34d033ee135c02cebcf7a086ce00595bd6b4174b`
[DaCe](https://github.com/spcl/dace), branch: `f2dace/dev` => commit hash: `8abc38060233d56a52ffa8e79c1ddeb8022f0f1d`
[icon-artifacts] https://github.com/spcl/icon-artifacts.git

## Generating Config-Injected Fortran Files and the SDFG

```bash
# First clone the icon-artifacts repository
# Switch to the working branch
git clone https://github.com/spcl/icon-artifacts.git
cd icon-artifacts
# Check out the latest commit that has been tested
git checkout bed6e8f
cd velocity

# To pull and re-generate data locally (assuming you are in icon-dace repo)
# Clone ICON DaCe Repository (Based on ICON Open-Source Release 2024.10)
# Check out to the latest test commit hash
git clone --recursive https://github.com/spcl/icon-dace
cd icon-dace
git checkout 34d033ee135c02cebcf7a086ce00595bd6b4174b
# Return to icon-artifacts repository root
cd ..

# Clone DaCe and switch to f2dace branch (that contains the f2dace frontend)
# Create a Python venv for the tested commit has
git clone --recursive dace f2dace
python -m venv .f2dace
source .f2dace/bin/activate
cd f2dace
pip install -e .
git checkout 8abc38060233d56a52ffa8e79c1ddeb8022f0f1d
# Return to icon-artifacts repository root
cd ..
```

```bash
# Replace paths with the checkut locations if necessary
# Path to ICON Dace example, assuming at repository root
# $(pwd) sohuld return <path/to/repo>/velocity right now
export ICON_DACE=$(pwd)/icon-dace
export ARTIFACTS=$(pwd)/generated_data
mkdir -p $(pwd)/velocity_checkpoints

# This needs to be called from the dace root
cd f2dace
python -m dace.frontend.fortran.tools.create_preprocessed_ast \
-i ${ICON_DACE}/src \
-i ${ICON_DACE}/externals/fortran-support/src \
-i ${ICON_DACE}/externals/cdi/src \
-i ${ICON_DACE}/externals/mtime/src \
-i ${ICON_DACE}/support \
-i ${ICON_DACE}/externals/math-support/src \
-i ${ICON_DACE}/externals/math-interpolation/src \
-i ${ICON_DACE}/externals/ecrad/utilities \
-o ${ARTIFACTS}/velocity.f90 \
-k mo_velocity_advection.velocity_tendencies \
--noop mo_exception.finish \
--noop mo_real_timer.timer_start \
--noop mo_real_timer.timer_stop \
--noop mo_real_timer.new_timer \
-d ${ARTIFACTS}/velocity_checkpoints
cd ..


# The velocity tendencies file that can be compiled as a single source is the output of the previous command.
# should be available under
${ARTIFACTS}/velocity.f90

# Before running next step, some manual changes are necessary. You need to remove `=> NULL()` with empty string
# The following command performs it:
sed 's/=> NULL()//g' "${ARTIFACTS}/velocity.f90" > velocity_modified.f90

cd f2dace
python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
-i ${ARTIFACTS}/velocity_modified.f90 \
-k mo_velocity_advection.velocity_tendencies \
-o ${ARTIFACTS}/velocity.sdfg \
-d ${ARTIFACTS}/velocity_checkpoints \
-c ${ARTIFACTS}/injected_configs
cd ..

# Generate Headers:
cd f2dace
python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp \
-i ${ARTIFACTS}/velocity_modified.f90 \
-g ${ARTIFACTS}/velocity.sdfg \
-f ${ARTIFACTS}/serde.f90 \
-c ${ARTIFACTS}/serde.h \
--config_inject ${ARTIFACTS}/injected_configs
cd ..

# The generated serge.h and velocity.sdfg need to be copied over from
# generated_data to folder above
cp generated_data/serde.h include
cp velocity.sdfg ./velocity_no_nproma.sdfgz

# Since CPU and GPU builds require different headers, the artifacts repository have multiple headers
# include/serde_velocity_no_proma.h
# include/serde_velocity_no_proma_gpu.h
# include/velocity_tendencies_no_nproma.h
# include/velocity_tendencies_no_nproma_gpu.h
# are currently used by the standalone pipeline.

# The velocity_tendencies_no_nproma.h and include/velocity_tendencies_no_nproma_gpu.h need to be manually generated
# although they are expected to be deterministic.
```

## Running ICON & Generating The Data For the Standalone Pipeline

```bash
# The generated data can be download using the following scripts:
./download_nproma32_data.sh
./download_nproma20480_data.sh

# If you want to regenerate the data by yourself for standalone testing
# Switch to the following branch of ICON-DaCe that has the synchronization for data added
cd icon-dace
git checkout yakup/ICON_24_10_merge_v2

mkdir -p build/verification
../../config/generic/gcc \
    CC=gcc \
    FC=gfortran \
    FCFLAGS="-g -O2 -I/usr/include/ -Wall -frecursive -Wno-unused-variable -Wno-unused-dummy-argument -Wno-unused-function -Wno-missing-include-dirs -DDACE_SUBST_VERIFY -DDACE_SUBST_ENABLE" \
    LDFLAGS="-L/usr/lib/x86_64-linux-gnu/ ${SDFG_LIB_PATHS}" \
    LIBS="-lnetcdff -lnetcdf -lopenblas ${SDFG_LIBS}" \
    --enable-acm-license \
    --disable-mixed-precision \
    --disable-edmf \
    --disable-les \
    --disable-ocean \
    --disable-jsbach \
    --disable-coupling \
    --disable-aes \
    --disable-rte-rrtmgp \
    --enable-ecrad \
    --disable-mpi \
    --disable-mpi-checks \
    --disable-openmp \
    --disable-loop-exchange \
    --enable-dace-subst=no \
    --enable-explicit-fpp \
    --disable-cdi-pio \
    --disable-grib2

make -j
./make_runscripts --all
cd run
cp -r ../../../grids/ ..
# For different nproma replace the line in the run config:
# For example:
# nproma                   =                   20480     ! loop number of cell blocks
./exp.exclaim_ape_R2B09.run

# Return to repo root when generting the data is done
cd ../../..

# The generate data needs to be manually copied to the paths
# <path/to/repo>/velocity/data_nproma<NPROMA>
# The standalone pipeline appends the environment variable NPROMA to the path, denoted with <NPROMA> above
# If the environment varaible is not set it will be defaulted to 20480 (and data_nproma20480), if generated data is copied to a different path
# update the NPROMA environment variable.
```

## Running the Standalone Pipeline
```bash
# Split the input SDFG to 4 configurations
python propagate_ifs.py
# Individually run each optimization step
for STAGE in {1..7}; do
    python -m utils.stages.compile_gpu_stage${STAGE} --optimize --compile
done
# If you want to run only the last step then you can run
# To only optimize the first 6 stages and run the obtained excetuable
# for nproma=32, nproma=20480, release and debug modes (4 in total)
# ./run.sh
```

## Obtaining & Integrating SDFG Library to ICON
```bash
# The library build assumes all input lives on the CPU at the entry of the call
# The changes to accept inputs to live on GPU require manual changes to the generated library.
# For the case where inputs live in the CPU:
# Change the compile action in:
# utils/stages/common.py
# change lib=False to lib=True in all `compile_if_propagated_sdfgs`
#    compile_if_propagated_sdfgs(
#        sdfgs, gpu=True, release=release,
#        generate_code=True, lib=False,
#        main_name="main.cu",
#        stage=stage,
#        debuginfo=False,
#        )

# To compile ICON with SDFG library enabled
git checkout yakup/ICON_24_10_merge_v2
# The SDFG_LIB_PATHS variable needs to include all compiled library locations. The SDFG_LIBS variable needs to have all library link commands (it should be the -l<sdfg name>).

export SDFG_LIB_PATHS="-L<path/to/sdfg_lib.so> -L..."
export SDFG_LIBS="-l<sdfg_name>"

# Depending on the mode you need to define the some compiler definitions.
# If you want substite Fortran function with SDFG (replace):
#-DDACE_SUBST_ENABLE

# If you want to just call Fortran functions:
# No definitions
# If you want to call both and numerically verify call:
# -DDACE_SUBST_ENABLE -DDACE_SUBST_VERIFY
./pipeline.sh
cd icon-scratchpad/icon-model
mkdir -p build/verification/
cd build/verification/
export SDFG_LIB_PATHS="-L$(pwd)/.dacecache/velocity/build"
export SDFG_LIBS="-lvelocity"
../../config/generic/gcc \
    CC=gcc \
    FC=gfortran \
    FCFLAGS="-g -O2 -I/usr/include/ -Wall -frecursive -Wno-unused-variable -Wno-unused-dummy-argument -Wno-unused-function -Wno-missing-include-dirs -DDACE_SUBST_VERIFY -DDACE_SUBST_ENABLE" \
    LDFLAGS="-L/usr/lib/x86_64-linux-gnu/ ${SDFG_LIB_PATHS}" \
    LIBS="-lnetcdff -lnetcdf -lopenblas ${SDFG_LIBS}" \
    --enable-acm-license \
    --disable-mixed-precision \
    --disable-edmf \
    --disable-les \
    --disable-ocean \
    --disable-jsbach \
    --disable-coupling \
    --disable-aes \
    --disable-rte-rrtmgp \
    --enable-ecrad \
    --disable-mpi \
    --disable-mpi-checks \
    --disable-openmp \
    --disable-loop-exchange \
    --enable-dace-subst=no \
    --enable-explicit-fpp \
    --disable-cdi-pio \
    --disable-grib2
# To return to root repo
cd ../../..

```
