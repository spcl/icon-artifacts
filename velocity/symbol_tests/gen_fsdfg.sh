export SPATH=$(pwd)
#cd $SCRATCH/dace
cd ~/Work/dace
git checkout f2dace-windmill
cd $SPATH


python -m dace.frontend.fortran.tools.create_preprocessed_ast \
       -i ./df.f90 \
       -o ./df_ast.f90 \
       -k kernel \
       --noop mo_exception.finish \
       --noop mo_real_timer.timer_start \
       --noop mo_real_timer.timer_stop

sed -i 's/LOGICAL(KIND *= *1)/INTEGER(KIND=4)/g' ./df_ast.f90

python -m dace.frontend.fortran.tools.create_singular_sdfg_from_ast \
    -i ./df_ast.f90 \
    -k kernel \
    -o ./df.sdfg

cd ~/Work/dace
git checkout f2dace-staging