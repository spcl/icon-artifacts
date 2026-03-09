#!/usr/bin/env bash
set -euo pipefail

DACE_DIR="${DACE_DIR:-$HOME/Work/dace}"
ORIG_DIR="$(pwd)"

echo "Using DaCe directory: $DACE_DIR"
cd "$DACE_DIR"

echo "Staging and pushing dace/transformation/layout to f2dace/dev..."
git add dace/transformation/layout
git add tests/layout
git commit -m "Update dace/transformation/layout from yakup/dev" || echo "Nothing to commit."
git push

echo "Checking out branch f2dace/staging..."
git checkout f2dace/staging
git pull

echo "Checking out dace/transformation/layout from yakup/dev..."
git checkout yakup/dev -- dace/libraries/environments
git checkout yakup/dev -- dace/libraries/standard/nodes/ttranspose.py
git checkout yakup/dev -- dace/transformation/layout
git checkout yakup/dev -- dace/sdfg/construction_utils.py
git checkout yakup/dev -- dace/sdfg/tasklet_utils.py
git checkout yakup/dev -- tests/layout

echo "Staging and pushing dace/transformation/layout to f2dace/staging..."
git add dace/transformation/layout
git add tests/layout
git add dace/sdfg/construction_utils.py
git add dace/sdfg/tasklet_utils.py
git commit -m "Update dace/transformation/layout from yakup/dev" || echo "Nothing to commit."
git push

cd "$ORIG_DIR"
echo "Done. Returned to $ORIG_DIR"
