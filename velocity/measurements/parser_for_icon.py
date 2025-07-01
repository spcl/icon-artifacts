import re
import statistics

def parse_runtime_file(filename):
    """
    Parse a file containing runtime information with istep and lvn_only parameters.
    Groups timing data into 4 bins based on istep (1,2) and lvn_only (0,1) values.
    """

    # Dictionary to store timing data for each configuration
    timing_data = {
        (1, 0): [],  # istep=1, lvn_only=0
        (1, 1): [],  # istep=1, lvn_only=1
        (2, 0): [],  # istep=2, lvn_only=0
        (2, 1): []   # istep=2, lvn_only=1
    }

    try:
        with open(filename, 'r') as file:
            lines = file.readlines()

        i = 0
        while i < len(lines):
            line = lines[i].strip()

            # Look for lines starting with "Called istep="
            if line.startswith("Called istep="):
                # Extract istep and lvn_only values using regex
                match = re.search(r'Called istep=(\d+), lvn_only=(\d+)', line)

                if match:
                    istep = int(match.group(1))
                    lvn_only = int(match.group(2))

                    # Check if next line contains elapsed time
                    if i + 1 < len(lines):
                        next_line = lines[i + 1].strip()

                        # Extract elapsed time using regex
                        time_match = re.search(r'Elapsed time \(seconds\):\s+([\d.E-]+)', next_line)

                        if time_match:
                            elapsed_time_seconds = float(time_match.group(1))
                            elapsed_time_microseconds = elapsed_time_seconds * 1_000_000

                            # Store timing data in appropriate bin
                            if (istep, lvn_only) in timing_data:
                                timing_data[(istep, lvn_only)].append(elapsed_time_microseconds)

                        # Skip the elapsed time line
                        i += 1

            i += 1

    except FileNotFoundError:
        print(f"Error: File '{filename}' not found.")
        return
    except Exception as e:
        print(f"Error reading file: {e}")
        return

    # Calculate and print statistics for each configuration
    for (istep, lvn_only), times in timing_data.items():
        if times:  # Only print if we have data
            mean_time = statistics.mean(times)
            median_time = statistics.median(times)

            print(f"Mean: {mean_time:.1f} µs, Median: {median_time:.1f} µs, "
                  f"(istep: {istep}, lvn Only: {lvn_only})")
        else:
            print(f"No data found for istep={istep}, lvn_only={lvn_only}")

# Main execution
if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        print("Usage: python script.py <filename>")
        print("Example: python script.py runtime_data.txt")
        sys.exit(1)

    filename = sys.argv[1]
    parse_runtime_file(filename)