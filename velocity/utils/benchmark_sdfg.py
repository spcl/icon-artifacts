import typing
import dace
import os

from dace.sdfg import is_devicelevel_gpu

import json

import shutil
from pathlib import Path

def instrument_sdfg(
    sdfgs: typing.List[dace.SDFG],
):
    for sdfg in sdfgs:
        sdfg.instrument = dace.InstrumentationType.Timer
        sdfg_name = sdfg.name

        kernels = []
        lib_nodes = []
        for node, graph in sdfg.all_nodes_recursive():
            if isinstance(node, dace.nodes.MapEntry):
                kernels.append((node, graph))

        for i, (kernel, graph) in enumerate(kernels):
            assert isinstance(kernel, dace.nodes.MapEntry)
            if kernel.map.schedule == dace.ScheduleType.GPU_Device:
                kernel.instrument = dace.InstrumentationType.GPU_Events
            else:
                if not isinstance(graph, dace.SDFGState):
                    for node, graph in sdfg.all_nodes_recursive():
                        if isinstance(node, dace.SDFGState):
                            if kernel in node.nodes():
                                state = node
                else:
                    state = graph
                    assert kernel in state.nodes()

                _sdfg = state.sdfg
                assert state in _sdfg.all_states()
                if not is_devicelevel_gpu(_sdfg, state, kernel):
                    kernel.instrument = dace.InstrumentationType.Timer

def get_all_paths(directory):
    paths = []
    for root, _, files in os.walk(directory):
        for name in files:
            paths.append(os.path.join(root, name))
    return paths


def collect_reports(
    sdfgs: typing.List[dace.SDFG],
):
    paths = get_all_paths(".dacecache/perf")
    for sdfg in sdfgs:
        report = None
        for path in paths:
            with open(path, "r") as f:
                _input = "\n".join(f.readlines())
                json_output = json.loads(_input)
                assert "sdfgHash" in json_output
                #print(json_output["sdfgHash"], sdfg.label, json_output["sdfgHash"] == sdfg.label)
                if json_output["sdfgHash"] == sdfg.label:
                    report = json_output
                    newperfpath = f".dacecache/{sdfg.label}/perf"
                    os.makedirs(newperfpath, exist_ok=True)
                    p = Path(path)
                    filename = p.name
                    shutil.copy(path, newperfpath + f"/{filename}")
        print(f"Report or SDFG: {sdfg.name} ({sdfg.label})")
        print(sdfg.get_latest_report_path())
        print(sdfg.get_latest_report())
        print(f"=" * 80)

def clean_reports(
    sdfgs: typing.List[dace.SDFG],
):
    for sdfg in sdfgs:
        sdfg.clear_instrumentation_reports()