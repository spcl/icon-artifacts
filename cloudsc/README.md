How to generate the `cloudsc.sdfg`.
```bash
python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast -i cloudsc.f90 -k cloudsc_driver_mod.cloudsc_driver -o cloudsc.sdfg -d cloudsc_checkpoints
```
