import typing
import dace
import os

from dace.sdfg import is_devicelevel_gpu


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
                kernels.append(node)

        for i, kernel in enumerate(kernels):
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

import json
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
                print(json_output["sdfgHash"], sdfg.label, json_output["sdfgHash"] == sdfg.label)
                if json_output["sdfgHash"] == sdfg.label:
                    report = json_output
        print(f"Report or SDFG: {sdfg.name} ({sdfg.label})")
        print(report)
        print(f"=" * 80)

def clean_reports(
    sdfgs: typing.List[dace.SDFG],
):
    for sdfg in sdfgs:
        sdfg.clear_instrumentation_reports()