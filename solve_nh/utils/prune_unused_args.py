import argparse
from pathlib import Path

from dace.frontend.fortran.ast_desugaring import (
    SPEC,
    alias_specs,
    search_real_local_alias_spec,
    remove_self,
    set_children,
    prune_unused_objects,
)
from dace.frontend.fortran.ast_utils import singular, children_of_type, atmost_one
from dace.frontend.fortran.fortran_parser import ParseConfig, create_fparser_ast
from fparser.two.Fortran2003 import (
    Program,
    Function_Stmt,
    Subroutine_Stmt,
    Function_Subprogram,
    Subroutine_Subprogram,
    Dummy_Arg_List,
    Dummy_Arg_Name_List,
    Execution_Part,
    Name,
)
from fparser.two.utils import walk


def prune_unused_arguments(ast: Program, targets: list[SPEC]) -> Program:
    alias_map = alias_specs(ast)

    for t in targets:
        if t not in alias_map:
            continue
        stmt = alias_map[t]
        if not isinstance(stmt, (Function_Stmt, Subroutine_Stmt)):
            continue
        fn = stmt.parent
        if not isinstance(fn, (Function_Subprogram, Subroutine_Subprogram)):
            continue
        fnargs = atmost_one(
            children_of_type(stmt, (Dummy_Arg_List, Dummy_Arg_Name_List))
        )
        fnargs = fnargs.children if fnargs else tuple()
        if not fnargs:
            continue
        all_args = set(a.string for a in fnargs)
        used_args = set()
        expart = atmost_one(children_of_type(fn, Execution_Part))
        if expart:
            for nm in walk(expart, Name):
                if nm.string not in all_args:
                    continue
                loc = search_real_local_alias_spec(nm, alias_map)
                if loc == t + (nm.string,):
                    used_args.add(nm.string)
        unused_args = all_args - used_args
        for ua in unused_args:
            uaspec = t + (ua,)
            assert uaspec in alias_map
            edecls = alias_map[uaspec].parent
            remove_self(alias_map[uaspec])
            if not edecls.children:
                remove_self(edecls.parent)
        fnargs = [a for a in fnargs if a.string in used_args]
        set_children(
            singular(children_of_type(stmt, (Dummy_Arg_List, Dummy_Arg_Name_List))),
            fnargs,
        )

    return ast


def main():
    argp = argparse.ArgumentParser()
    argp.add_argument(
        "-i",
        "--in_src",
        type=str,
        required=True,
        action="append",
        default=[],
        help="The files or directories containing Fortran source code (absolute path or relative to CWD)."
        "Can be repeated to include multiple files and directories.",
    )
    argp.add_argument(
        "-k",
        "--entry_point",
        type=str,
        required=True,
        action="append",
        default=[],
        help="The entry points which should be kept with their dependencies (can be repeated)."
        "Specify each entry point as a `dot` separated path through named objects from the top.",
    )
    argp.add_argument(
        "-o",
        "--output_ast",
        type=str,
        required=False,
        default=None,
        help="(Optional) A file to write the preprocessed AST into (absolute path or relative to CWD)."
        "If nothing is given, then will write to STDOUT.",
    )
    args = argp.parse_args()
    entry_points = [tuple(ep.split(".")) for ep in args.entry_point]

    cfg = ParseConfig(sources=[Path(p) for p in args.in_src], entry_points=entry_points)
    ast = create_fparser_ast(cfg)
    ast = prune_unused_arguments(ast, cfg.entry_points)
    ast = prune_unused_objects(ast, cfg.do_not_prune)
    f90 = ast.tofortran()

    if args.output_ast:
        with open(args.output_ast, "w") as f:
            f.write(f90)
    else:
        print("Preprocessed Fortran AST:\n===")
        print(f90)


if __name__ == "__main__":
    main()
