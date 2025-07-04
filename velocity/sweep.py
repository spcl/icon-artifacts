import subprocess
import os

# Default parameters
x_coarsenings = [1, 2, 4]
y_coarsenings = [1, 2, 4]
x_block_sizes = [32, 64, 128, 256]
y_block_sizes = [1, 2, 4, 8]
valid_products = [256, 512]
y_unroll_factors = [1, 2]

tested_log = "tested_params.log"

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
    print(f"=== Running for {label} ===")

    env = os.environ.copy()
    env["_RELEASE"] = "TRUE"
    env["_USE_CUDA_EVENTS"] = "FALSE"
    env["_USE_NVHPC"] = "FALSE"
    env["X_COARSENING"] = str(x_c)
    env["Y_COARSENING"] = str(y_c)
    env["X_BLOCK_SIZE"] = str(x_bs)
    env["Y_BLOCK_SIZE"] = str(y_bs)
    env["Y_UNROLL"] = str(y_unroll)

    try:
        subprocess.run(
            ["python", "-m", "utils.stages.compile_gpu_stage8", "--optimize", "--compile"],
            check=True,
            env=env
        )
    except subprocess.CalledProcessError:
        print("❌ Compilation failed for this config")
        return

    try:
        with open("tile.log", "a") as logf:
            print(f"=== Running for {label} ===", file=logf)
            logf.flush()
            subprocess.run(["./velocity_gpu.stage8", "7"], stdout=logf, check=True, env=env)
            logf.flush()
    except subprocess.CalledProcessError:
        print("❌ Execution failed for this config")

run_config(1, 1, 256, 1, 1)

# Run all other valid combinations
for y_unroll in y_unroll_factors:
    for x_c in x_coarsenings:
        for y_c in y_coarsenings:
            for x_bs in x_block_sizes:
                for y_bs in y_block_sizes:
                    if (x_c, y_c, x_bs, y_bs) == (1, 1, 256, 1):
                        continue  # already handled
                    run_config(x_c, y_c, x_bs, y_bs, y_unroll)
