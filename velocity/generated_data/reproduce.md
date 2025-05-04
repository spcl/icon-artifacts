# Generate SDFG and Data

The branches and commits used to generate the data are:
[icon-dace](https://github.com/spcl/icon-dace), branch: `pratyai/working-patches-2024.10` => commit hash: `34d033ee135c02cebcf7a086ce00595bd6b4174b`
[DaCe](https://github.com/spcl/dace), branch: `f2dace/dev` => commit hash: `8abc38060233d56a52ffa8e79c1ddeb8022f0f1d`

All scripts need to be run from DaCe root

Replace paths with the checkedout locations
```bash
# Path to ICON Dace
export ICON_DACE=/home/primrose/Work/IconGrounds/icon-dace2
# Path for Outputs (within artifacts repo)
export ARTIFACTS=/home/primrose/Work/IconGrounds/icon-artifacts/velocity/generated_data

mkdir -p ~/Downloads/velocity_checkpoints
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
```

The velocity tendencies file that can be compiled as a single source is the output of the previous command.
```bash
${ARTIFACTS}/velocity.f90
```

Before running next step, some manual changes are necessary. You need to remove `=> NULL()` with empty string

```bash
sed 's/=> NULL()//g' "${ARTIFACTS}/velocity.f90" > velocity_modified.f90

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
-i ${ARTIFACTS}/velocity_modified.f90 \
-k mo_velocity_advection.velocity_tendencies \
-o ${ARTIFACTS}/velocity.sdfg \
-d ${ARTIFACTS}/velocity_checkpoints
```

Generate Headers:
```bash
python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp \
    -i ${ARTIFACTS}/velocity_modified.f90 \
    -g ${ARTIFACTS}/velocity.sdfg \
    -f ${ARTIFACTS}/serde.f90 \
    -c ${ARTIFACTS}/serde.h
```

# ICON (Running and Getting Data)

```bash
git checkout yakup/ICON_24_10_merge_v2
```

```bash
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
```

```bash
make -j
./make_runscripts --all
cd run
cp -r ../../../grids/ ..
./exp.exclaim_ape_R2B09.run
```

For different nproma replace the line in the run config:
```bash
nproma                   =                   20480     ! loop number of cell blocks
```