set -xe

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