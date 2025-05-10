### How To Generate Stage Artefacts?

#### 1. Be in the `velocity` directory:
```commandline
(base) [pmazumde@ault velocity]$ pwd
/scratch/pmazumde/dycon/icon-artifacts/velocity
```

#### 2. Run If-Propagation if necessary:

```commandline
python propagate_ifs.py
```

#### 3. Run the script for that specific stage

The example shown here is for stage#1. Note that the `python -m` style call is needed for now.
```commandline
python -m utils.stages.compile_cpu_stage1
```
This will both optimize the graph and then compile into a C++ library (assuming the input graph already exists).

If you only want to optimize the graph:
```commandline
python -m utils.stages.compile_cpu_stage1 --optimize
```

If you only want to compile the output graph (assuming the optimized output graph already exists):
```commandline
python -m utils.stages.compile_cpu_stage1 --compile
```

---

There is no caching behaviour (intentionally so). The compiled binaries still overwrite each other. So for now, to do numerical validation use the compile-only version for a stage, and then validate separately.