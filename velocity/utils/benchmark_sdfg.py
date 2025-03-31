import typing
import dace
import os


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
            if kernel.map.schedule == dace.ScheduleType.GPU_Device:
                kernel.instrument = dace.InstrumentationType.GPU_Events
            else:
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