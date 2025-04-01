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


def collect_reports(
    sdfgs: typing.List[dace.SDFG],
):
    for sdfg in sdfgs:
        report = sdfg.get_latest_report()
        print(f"Report or SDFG: {sdfg.name}, {sdfg.label}")
        print(f"Report path: {sdfg.get_latest_report_path()}")
        print(report)
        print(f"=" * 80)

def clean_reports(
    sdfgs: typing.List[dace.SDFG],
):
    for sdfg in sdfgs:
        sdfg.clear_instrumentation_reports()