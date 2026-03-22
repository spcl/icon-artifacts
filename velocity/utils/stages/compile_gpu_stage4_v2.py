import dace
from dace.transformation.passes import InlineSDFGs
from dace.transformation.dataflow import MapCollapse, MapFusion
import utils.stages.common as common
import utils.config as config
from utils.unique_names import unique_names
from utils.benchmark_sdfg import instrument_sdfg
from utils.compile_if_propagated_sdfgs import compile_if_propagated_sdfgs
from utils.map_state_fission import MapStateFission
from utils.prune_unused_inputs_outputs import prune_unused_inputs_outputs
import argparse
from utils.propagate_if_cond import propagate_if_cond
from utils.demote_symbol_to_scalar import demote_symbol_to_scalar
import os

STAGE_ID = 4


def optimization_action(sdfg):
    """ DEFINE THE OPTIMIZATION ACTION HERE """
    sdfg.validate()
    sdfg.simplify(skip=["StateFusion"])
    sdfg.validate()

    prune_unused_inputs_outputs(sdfg)

    InlineSDFGs().apply_pass(sdfg, {})
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapFusion)
    for n, g in sdfg.all_nodes_recursive():
        if isinstance(n, dace.nodes.NestedSDFG):
            if isinstance(n, dace.nodes.NestedSDFG):
                k = n.sdfg.apply_transformations_repeated(MapFusion, permissive=True)
                if config.verbose:
                    print(f"Applied MapFusion {k} time(s) to NestedSDFG {n.sdfg.name}")

    if config.verbose:
        print(f"Applied MapFusion {k} time(s)")
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    sdfg.simplify(skip=["StateFusion"])
    prune_unused_inputs_outputs(sdfg)
    InlineSDFGs().apply_pass(sdfg, {})
    k = sdfg.apply_transformations_repeated(MapCollapse, permissive=True)
    if config.verbose:
        print(f"Applied MapCollapse {k} time(s)")

    sdfg.simplify(skip=["StateFusion"])
    # I saw trurthy ifs, propagate those conditions and try to fuse states agian
    # TODO: Crashes sometimes
    propagate_if_cond(sdfg, sdfg, None, None, True)
    # Prevents some transformations from being applied
    # This is not a symbol anymore (? - it was before why)
    # TODO: Check if this is necessary, if so fix
    assert "tmp_call_18" in sdfg.symbols
    if "tmp_call_18" in sdfg.symbols:
        demote_symbol_to_scalar(sdfg, "tmp_call_18")

    sdfg.validate()
    sdfg.simplify(skip=["StateFusion"])
    sdfg.validate()
    return sdfg

import sys

def main():
    argp = argparse.ArgumentParser()
    argp.add_argument('--optimize',     action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--compile',      action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--unpermuted',   action=argparse.BooleanOptionalAction, default=False)
    argp.add_argument('--permutations', type=str, default=None,
                      help='Comma-separated config names from PERMUTE_CONFIGS')
    args = argp.parse_args()

    if not args.optimize and not args.compile:
        args.optimize, args.compile = True, True

    names = common.sdfg_names()

    # ------------------------------------------------------------------
    # Optimize
    # ------------------------------------------------------------------
    if args.optimize:
        for name in names:
            infile  = common.stage_input(name,  STAGE_ID)
            outfile = common.stage_output(name, STAGE_ID)
            print(f"Stage #{STAGE_ID}: Optimising {name} from {infile}")
            sdfg = dace.SDFG.from_file(infile)
            sdfg.name = name
            sdfg.validate()
            sdfg = optimization_action(sdfg)
            print(f"Stage #{STAGE_ID}: Saved as {outfile}")
            sdfg.save(outfile, compress=True)

    # ------------------------------------------------------------------
    # Compile unpermuted baseline
    # ------------------------------------------------------------------
    if args.unpermuted:
        from sc26_layout.permute_stage4 import add_timers

        print(f"=== Compiling unpermuted baseline ===")
        sdfgs = {
            name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID))
            for name in names
        }
        nsdfgs = {}
        for name, sdfg in sdfgs.items():
            add_timers(sdfg)
            # insert_synchronization_for_profiling(sdfg)
            sdfg.validate()
            sdfg.validate()
            nsdfgs[name] = sdfg

        common.compile_action(
            STAGE_ID, nsdfgs, False, None, False,
            name_suffix="_unpermuted",
            main_name="main_per.cu",
            tblock_dim=_TBLOCK_DIM,
            stage_suffix="_unpermuted",
        )
        return

    # ------------------------------------------------------------------
    # Compile permuted variants (both shuffled and unshuffled)
    # ------------------------------------------------------------------
    if args.compile:
        from sc26_layout.permute_stage4 import (
            PERMUTE_CONFIGS,
            permute_sdfg,
        )

        if args.permutations:
            config_names = [c.strip() for c in args.permutations.split(",")]
        else:
            config_names = ["cv1_ch1_f1_s1_n201"]   # default: all-groups config

        for config_name in config_names:
            if config_name not in PERMUTE_CONFIGS:
                print(f"Unknown config: {config_name}. "
                      f"Available: {list(PERMUTE_CONFIGS.keys())}", file=sys.stderr)
                sys.exit(1)

            for shuffle_map in [True, False]:
                shuffle_label = "ms" if shuffle_map else "mu"
                print(f"=== Compiling config: {config_name} ({shuffle_label}) ===")

                sdfgs = {
                    name: dace.SDFG.from_file(common.stage_output(name, STAGE_ID))
                    for name in names
                }
                nsdfgs = {}
                for name, sdfg in sdfgs.items():
                    sdfg = permute_sdfg(
                        sdfg,
                        config_name=config_name,
                        shuffle_map=shuffle_map,
                    )
                    # insert_synchronization_for_profiling(sdfg)
                    sdfg.validate()
                    sdfg.validate()
                    nsdfgs[name] = sdfg

                suffix = f"_permuted_{config_name}_{shuffle_label}"
                common.compile_action(
                    STAGE_ID, nsdfgs, False, None, False,
                    name_suffix=suffix,
                    main_name="main_per.cu",
                    tblock_dim=_TBLOCK_DIM,
                    stage_suffix=suffix,
                )

if __name__ == "__main__":
    main()
