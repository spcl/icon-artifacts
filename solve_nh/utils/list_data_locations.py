from pathlib import Path
import dace

path = Path(__file__).parent.parent

sdfg_paths = {
    path / "codegen" / "gpu_solve_nh_corrector_post_stage3.sdfgz",
    path / "codegen" / "gpu_solve_nh_corrector_pre_stage3.sdfgz",
    path / "codegen" / "gpu_solve_nh_predictor_pre.sdfgz",
    path / "codegen" / "gpu_solve_nh_predictor_post.sdfgz",
}

report_paths = {
    path / "gpu_solve_nh_corrector_post_stage3_data_report.txt",
    path / "gpu_solve_nh_corrector_pre_stage3_data_report.txt",
    path / "gpu_solve_nh_predictor_pre_stage3_data_report.txt",
    path / "gpu_solve_nh_predictor_post_stage3_data_report.txt",
}

def list_data_locations():
    for sdfg_path in sdfg_paths:
        sdfg = dace.SDFG.from_file(sdfg_path)
        for state in sdfg.all_states():
            for node in state.nodes():
                if isinstance(node, dace.nodes.AccessNode):
                    pass