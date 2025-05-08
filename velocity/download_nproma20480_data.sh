#!/bin/bash

# Set the URL and output directory
# NOTE: Use `patch_out_is_associated.sh` to patch the data out of the two `..._is_associated` struct members.
URL="https://polybox.ethz.ch/index.php/s/WoxiditKJjgdEfR/download/nproma20480_data_files.tar.xz"
OUTPUT_DIR="data_nproma20480"
TAR_FILE="nproma20480_data_files.tar.xz"

# Check if the output directory already exists
if [ -d "$OUTPUT_DIR" ]; then
  echo "Directory '$OUTPUT_DIR' already exists. Skipping download and extraction."
else
  # Download the file
  echo "Downloading file..."
  curl -L -o "$TAR_FILE" "$URL"
fi

# Create output directory
mkdir -p "$OUTPUT_DIR"

# Extract the file into the output directory
echo "Extracting to $OUTPUT_DIR..."
tar -xf "$TAR_FILE" -C "$OUTPUT_DIR"

# Clean up
rm "$TAR_FILE"

echo "Done."

