# Recipes

## Generateing SDFGs from "fake" DyCore

Assumption: You are in this directory (`icon-artifacts/solve_nh`). Fake DyCore is in `./edited-src/solve_nh_fake.f90`. You want to generate SDFGs for sthe 4 parts of `solve_nh()` routine (`predictor_pre` etc.).

```bash
# Regenerate the single preprocessed AST
bash regen-ast.sh
# Regenerate all 4 SDFG
bash regen-sdfgs.sh
# Regenerate all 4 serialization/deserialization modules
bash regen-serde.sh
```

## Running a Stage

Assumption: You are in this directory (`icon-artifacts/solve_nh`). You want to run `stage_0`.

```bash
# Run all the actions
python -m stages.stage_0

# Run only the SDFG optimization action
python -m stages.stage_0 --optimize

# Run only the code-generation action
python -m stages.stage_0 --codegen

# Run only the standalone compilation action
python -m stages.stage_0 --compile
```

After the standalone compilation action, you should have a binary `./verify_solve_nh_parts` in this directory.

## Validating Numerically

Assumptions: You have compiled and have the `./verify_solve_nh_parts` binary. You also have the serialized data somewhere (e.g. in `/tmp/dycore-data`). You can download the [sample data here](https://polybox.ethz.ch/index.php/s/FQAN7NfnRzS9kdt).

```bash
# Run the standalone binary, with data from `/tmp/dycore-data` and at timestep `20`.
./verify_solve_nh_parts --data=/tmp/dycore-data 20
```

NOTE: Sometimes it crashes at the very end, when writing the data. You can rerun, and it cleanly exits after a few times. Often you can also just ignore the error (may cause some missing lines, but the remaining information often suffices).

At this point, there should be a `./gotwant/dycore-data` directory with the files to compare. Now you can run the comparison script.

```bash
python -m utils.compare_got_want -r gotwant/dycore-data
```
