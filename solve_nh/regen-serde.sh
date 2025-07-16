set -xe

python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp -i solve_nh_fake.f90 -g solve_nh_predictor_pre.sdfgz -f edited-src/predictor_pre_serde.f90 -c include/predictor_pre_serde.h -m predictor_pre
python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp -i solve_nh_fake.f90 -g solve_nh_predictor_post.sdfgz -f edited-src/predictor_post_serde.f90 -c include/predictor_post_serde.h -m predictor_post
python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp -i solve_nh_fake.f90 -g solve_nh_corrector_pre.sdfgz -f edited-src/corrector_pre_serde.f90 -c include/corrector_pre_serde.h -m corrector_pre
python -m dace.frontend.fortran.tools.generate_serde_f90_and_cpp -i solve_nh_fake.f90 -g solve_nh_corrector_post.sdfgz -f edited-src/corrector_post_serde.f90 -c include/corrector_post_serde.h -m corrector_post

perl -pi -E 's/(->__f2dace_.*?_d_[0-9]+_s)_[0-9]+/$1/g' include/*_serde.h
perl -pi -E 's/read_line\(s, \{"# diag"\}\);/read_until(s, {"# diag"});/g' include/*_serde.h  # TODO: Remove after regenerating data files.
