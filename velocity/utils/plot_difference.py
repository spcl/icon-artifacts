import numpy as np
import matplotlib.pyplot as plt

def read_arrays_from_file(file_path):
    """Read arrays of floating-point numbers from a structured file."""
    with open(file_path, "r") as f:
        lines = f.readlines()

    data_arrays = []
    current_array = []
    in_entries_section = False

    prev_line = None
    arr_name = None
    for line in lines:
        line = line.strip()
        if line == "# entries":
            if current_array:
                data_arrays.append((arr_name, np.array(current_array)))  # Save the previous array
                current_array = []
                arr_name = None
            in_entries_section = True
            continue

        if in_entries_section:
            try:
                current_array.append(float(line))
            except ValueError:
                # Stop reading when we hit non-float data
                if current_array:
                    data_arrays.append((arr_name, np.array(current_array)))
                    current_array = []
                    arr_name = None
                in_entries_section = False

        if "# assoc" in line:
            print(prev_line)
            arr_name = prev_line.split("# ")[-1]
        prev_line = line

    if current_array:
        data_arrays.append(np.array(current_array))  # Save the last array

    return data_arrays

def plot():
    for name in ["z_w_concorr_me", "global_data", "p_diag", "p_metrics", "p_prog", "z_vt_ie", "z_kin_hor_e"]:
        for i in range(1, 5):
            file_want = f"{name}_{i}.want"
            file_got = f"{name}_{i}.got"

            # Read all arrays from both files
            want_arrays = read_arrays_from_file(file_want)
            got_arrays = read_arrays_from_file(file_got)

            for idx, ((arr_name, want_data), (arr_name2, got_data)) in enumerate(zip(want_arrays, got_arrays)):
                plt.clf()

                # Ensure the arrays have the same size
                assert len(want_data) == len(got_data)
                min_length = min(len(want_data), len(got_data))
                want_data, got_data = want_data[:min_length], got_data[:min_length]

                # Calculate absolute difference
                absolute_difference = np.abs(want_data - got_data)
                m = max(absolute_difference)
                mi = min(absolute_difference)
                print(f"Max absolute difference for {arr_name} is {m}, min: {mi}, len {len(absolute_difference)}")

                # Plot
                plt.plot(absolute_difference, label=f"Absolute Difference {arr_name}")
                plt.xlabel("Index")
                plt.ylabel("Absolute Difference")
                plt.ylim(0, 1.1*m)
                plt.title(f"Absolute Difference for Array {arr_name}")
                plt.legend()
                plt.grid(True)
                plt.savefig(f"{name}_{i}_array_{arr_name}.png")

if __name__ == "__main__":
    plot()