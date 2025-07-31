# Regenerating Headers for Velocity

- (Branch: `new_sched_solve_nh`) Generate and build velocity tendencies `stage_9` on GPU
- (Branch: `new_sched_solve_nh`) Collect declerations using `collect_headers.py` in the `velocity` sub-folder, copy the content from this branch to `velocity_gpu.h` in `pratyai/solve_nh`.
- (Branch: `new_sched_solve_nh`) Go to `include` folder, format the `velocity_gpu.h` using the `.clang-format` in the same folder.
- (Branch: `pratyai/solve_nh`) Delete `name_mappings.py` if exist, call `python utils/generate_headers.py` and generate `name_mappings.py`
- (Branch: `pratyai/solve_nh`) Copy the content of `name_mappings.py` to `utils/reinject_velocity_tasklet.py` the name mappings is used by the `reinject` function to generate the GPU-integration tasklet for velocity tendencies.

# Building

## DyCore
`pratyai/solve_nh` + `f2dace/staging` to build DyCore


## Velocity
`new_sched_solve_nh` + `f2dace/staging` to build velocity tendencies.
Call: `python -m stages.stage_8` for the last standalone version.
Call: `python -m stages.stage_9` for the last library version.
If you change stage `i` all stages after `i` needs to be updated.
To build libraries: `build_libs.sh`

# Tiling

TODO
