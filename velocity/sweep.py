import subprocess
import os

# Default parameters
x_coarsenings = [1, 2]
y_coarsenings = [1, 2, 4]
x_block_sizes = [256, 128]
y_block_sizes = [1, 2]
valid_products = [256]
y_unroll_factors = [1, 2]

tested_log = "logs/tested_params.log"
compare_log = "logs/compare.log"

# Read previously tested configs
if os.path.exists(tested_log):
    with open(tested_log) as f:
        tested = set(line.strip() for line in f)
else:
    tested = set()

def run_config(x_c, y_c, x_bs, y_bs, y_unroll):
    label = f"x_c={x_c}, y_c={y_c}, x_bs={x_bs}, y_bs={y_bs}, y_unroll={y_unroll}"
    if f"=== Running for {label} ===" in tested:
        return

    total = x_bs * y_bs
    if total not in valid_products:
        return

    if y_unroll > y_c:
        return  # y_unroll cannot exceed y_coarsening

    with open(tested_log, "a") as logf:
        print(f"=== Running for {label} ===", file=logf)
    with open(compare_log, "a") as comparef:
        print(f"=== Running for {label} ===", file=comparef)
    print(f"=== Running for {label} ===")

    env = os.environ.copy()
    env["_RELEASE"] = "1"
    env["_USE_CUDA_EVENTS"] = "0"
    env["_USE_NVHPC"] = "1"
    env["_TILE"] = "1"
    env["_PROFILE"] = "1"
    env["_BUILD_FOR_SOLVE_NH_INTEGRATION"] = "0"
    env["_REDUCE_BITWIDTH_TRANSFORMATION"] = "0"
    env["X_COARSENING"] = str(x_c)
    env["Y_COARSENING"] = str(y_c)
    env["X_BLOCK_SIZE"] = str(x_bs)
    env["Y_BLOCK_SIZE"] = str(y_bs)
    env["Y_UNROLL"] = str(y_unroll)

    try:
        subprocess.run(
            ["python", "-m", "utils.stages.compile_gpu_stage8", "--compile"],
            check=True,
            env=env
        )
    except subprocess.CalledProcessError:
        print("❌ Compilation failed for this config")
        return

    try:
        env["REPS"] = "1"
        subprocess.run(["./velocity_gpu.stage8_standalone_release"], stdout=logf, check=True, env=env)
    except subprocess.CalledProcessError:
        print("❌ First execution failed for this config")

    try:
        subprocess.run(
            ["python", "utils/compare_got_and_want.py", "--root=gotwant/data_nproma20480"],
            stdout=comparef,
            check=True,
            env=env
        )
    except subprocess.CalledProcessError:
        print("❌ Numerical comparison crashed for this config")
        return

    try:
        with open("logs/tile.log", "a") as logf:
            print(f"=== Running for {label} ===", file=logf)
            logf.flush()
            env["REPS"] = "50"
            subprocess.run(["./velocity_gpu.stage8_standalone_release"], stdout=logf, check=True, env=env)
            logf.flush()
    except subprocess.CalledProcessError:
        print("❌ Profiling execution failed for this config")


# Run all other valid combinations
for x_bs in x_block_sizes:
    for y_bs in y_block_sizes:
        for y_unroll in y_unroll_factors:
            for x_c in x_coarsenings:
                for y_c in y_coarsenings:
                    run_config(x_c, y_c, x_bs, y_bs, y_unroll)
