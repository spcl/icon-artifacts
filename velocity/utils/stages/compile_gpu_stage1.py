import dace
from dace.transformation.interstate import ContinueToCondition
from dace.transformation.passes import StructToContainerGroups, SymbolPropagation, ConstantPropagation
from utils.clean_bad_views import clean_bad_views
import utils.stages.common as common
import utils.config as config
from utils.reductions import add_all_reductions
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
import argparse
from utils.init_transient_zero import init_transient_zero
from utils.reassign_vars import reassign_vars
STAGE_ID = 1


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    # Tests: (Clean Bad Views is mandatory)
    # StructToContainerGroups => OK
    # ContinueToCondition + StructToContainerGroups => OK
    # ContinueToCondition + StructToContainerGroups + Simplify + SymbolProp + Simplify => ? (probably OK, untested)
    # ContinueToCondition + StructToContainerGroups + Simplify + SymbolProp + Simplify + Reduction => OK
    # Need to remove partial view towers (it is illegal and should not happen, but it happens)
    clean_bad_views(sdfg)
    sdfg.apply_transformations_repeated(ContinueToCondition) # To RM continue blocks - this could made into a nice transformation (living in Main)
    # Flattening needs to run before everything
    StructToContainerGroups(
        validate=False,
        save_steps=False,
        verbose=config.verbose,
        simplify=False,
        interface_with_struct_copy=True,
        interface_to_gpu=False,
        clean_trivial_views=True,
        shallow_copy=False,
        shallow_copy_to_gpu=False,
        taskloop = False,
    ).apply_pass(sdfg, {}) # Flattening pass
    sdfg.simplify(skip=["ArrayElimination"])
    SymbolPropagation().apply_pass(sdfg, {}) # Like ConstProp TODO: can be made into a proper transformation
    sdfg.simplify(skip=["ArrayElimination"]) # ArrayElimination breaks the SDFG (might be f2dace related)
    if config.reduction:
        add_all_reductions(sdfg) # Name matched reductions - major work necessary to have a "detect reduction" pass
    # init_transient_zero(sdfg)
    # It is here to get rid of redundant symbols like `ol_size` (which are not correctly handled in other hacks later).
    ConstantPropagation().apply_pass(sdfg, {})
    return sdfg

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize', action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile', action=argparse.BooleanOptionalAction, default=False)
    args = argp.parse_args()
    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True

    names = common.sdfg_names()

    if args.optimize:
      for name in names:
          infile = common.stage_input(name, STAGE_ID)
          outfile = common.stage_output(name, STAGE_ID)

          print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")

          sdfg = dace.SDFG.from_file(infile)
          sdfg.name = name
          sdfg.validate()

          sdfg = optimization_action(sdfg)

          print(f"Stage #{STAGE_ID}: Saved as {outfile}")
          sdfg.save(outfile, compress=True)

    if args.compile:
        # Read back the written files as we prepare for compilation.
        sdfgs = {name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID)) for name in names}
        common.compile_action(STAGE_ID, sdfgs, False, None, False)

if __name__ == "__main__":
    main()
