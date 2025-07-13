sed -E '/^[[:space:]]*include[[:space:]]+('\''[^'\'']+'\''|"[^"]+")[[:space:]]*$/Id' edited-src/solve_nh_fake.f90 > solve_nh_fake.f90

python -m dace.frontend.fortran.tools.create_preprocessed_ast \
  -i solve_nh_fake.f90 \
  -i ~/gitspace/icon-dace-patched/src \
  -i ~/gitspace/icon-dace-patched/src/io/shared \
  -i ~/gitspace/icon-dace-patched/externals/ecrad/utilities \
  -i ~/gitspace/icon-dace-patched/externals/math-support/src \
  -i ~/gitspace/icon-dace-patched/externals/math-interpolation/src \
  -i ~/gitspace/icon-dace-patched/externals/fortran-support/src \
  -i ~/gitspace/icon-dace-patched/externals/cdi/src \
  -i ~/gitspace/icon-dace-patched/externals/mtime/src \
  -i ~/gitspace/icon-dace-patched/src/io/shared \
  -i ~/gitspace/icon-dace-patched/support/mo_util_uuid_types.f90 \
  -o solve_nh_fake.f90 \
  -d delete-me \
  -k fake_mo_solve_nonhydro.solve_nh_predictor_pre \
  -k fake_mo_solve_nonhydro.solve_nh_predictor_post \
  -k fake_mo_solve_nonhydro.solve_nh_corrector_pre \
  -k fake_mo_solve_nonhydro.solve_nh_corrector_post

cp solve_nh_fake.f90 solve_nh_fake.f90.bak \
  && sed -E -e 's/[[:space:]]*=>[[:space:]]*null\([[:space:]]*\)//Ig' solve_nh_fake.f90.bak > solve_nh_fake.f90
cp solve_nh_fake.f90 solve_nh_fake.f90.bak \
  && sed -E -e 's/\(process_mpi_all_size <= 1\)/.TRUE./Ig' solve_nh_fake.f90.bak > solve_nh_fake.f90
cp solve_nh_fake.f90 solve_nh_fake.f90.bak \
  && awk '
    BEGIN {skip=0}
    /IF *\(generation == 20\) *THEN/ {skip=1; next}
    skip && /END *IF/ {skip=0; next}
    !skip {print}
  ' solve_nh_fake.f90.bak > solve_nh_fake.f90
rm solve_nh_fake.f90.bak

#python -m utils.prune_unused_args \
#  -i solve_nh_fake.f90 \
#  -o solve_nh_fake.f90 \
#  -k fake_mo_solve_nonhydro.solve_nh_predictor_pre \
#  -k fake_mo_solve_nonhydro.solve_nh_predictor_post \
#  -k fake_mo_solve_nonhydro.solve_nh_corrector_pre \
#  -k fake_mo_solve_nonhydro.solve_nh_corrector_post

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
  -i solve_nh_fake.f90 \
  -k fake_mo_solve_nonhydro.solve_nh_predictor_pre \
  -o solve_nh_predictor_pre.sdfgz \
  --keep_components \
  -d delete-me

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
  -i solve_nh_fake.f90 \
  -k fake_mo_solve_nonhydro.solve_nh_predictor_post \
  -o solve_nh_predictor_post.sdfgz \
  --keep_components \
  -d delete-me

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
  -i solve_nh_fake.f90 \
  -k fake_mo_solve_nonhydro.solve_nh_corrector_pre \
  -o solve_nh_corrector_pre.sdfgz \
  --keep_components \
  -d delete-me

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
  -i solve_nh_fake.f90 \
  -k fake_mo_solve_nonhydro.solve_nh_corrector_post \
  -o solve_nh_corrector_post.sdfgz \
  --keep_components \
  -d delete-me