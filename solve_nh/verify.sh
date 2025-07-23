#!/bin/bash

set -e

print_usage() {
  echo "Usage: $0 <stage_number> [--all]"
  exit 1
}

if [[ $# -lt 1 ]]; then
  print_usage
fi

STAGE_NUM=$1
OPT_ALL=false

if [[ "$2" == "--all" ]]; then
  OPT_ALL=true
fi

# Optimize stages
if $OPT_ALL; then
  for ((i=0; i<STAGE_NUM; i++)); do
    echo "Optimizing stage $i..."
    if [[ $i -eq 0 ]]; then
      python -m stages.stage_0 --shim --optimize --codegen 1>opt_stage0.out 2>opt_stage0.err
    else
      python -m stages.stage_$i --optimize --codegen --compile 1>opt_stage$i.out 2>opt_stage$i.err
    fi
  done
else
  echo "Optimizing stage $STAGE_NUM..."
  if [[ $STAGE_NUM -eq 0 ]]; then
    python -m stages.stage_0 --shim --optimize --codegen 1>opt_stage0.out 2>opt_stage0.err
  else
    python -m stages.stage_$STAGE_NUM --optimize --codegen --compile 1>opt_stage$STAGE_NUM.out 2>opt_stage$STAGE_NUM.err
  fi
fi

# Run verification and comparison
echo "Running verification for stage $STAGE_NUM..."
./verify_solve_nh_parts --data=dycore-data 1>run_stage$STAGE_NUM.out 2>run_stage$STAGE_NUM.err

echo "Comparing results for stage $STAGE_NUM..."
python utils/compare_got_want.py --root=gotwant/dycore-data 1>compare_stage$STAGE_NUM.out 2>compare_stage$STAGE_NUM.err
