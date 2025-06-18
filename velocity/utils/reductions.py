import dace
from dace.libraries.standard import CodeLibraryNode
from dace.properties import make_properties, Property
from utils import find_node_by_name
from dace.transformation.passes.analysis import loop_analysis
from dace.sdfg.state import ControlFlowRegion, LoopRegion, ConditionalBlock

reduction_code_dict = {
    "maxZ_to_scalar_device": f"""
{{
    double max_val = 0.0;
    #pragma unroll
    for (int i = 0; i < in_size; i++){{
        max_val = (in_arr[i] > max_val) ? in_arr[i] : max_val;
    }}
    out = max_val;
}}
""",
    "maxZ_to_address_device": f"""
{{
    double max_val = 0.0;
    #pragma unroll
    for (int i = 0; i < in_size; i++){{
        max_val = (in_arr[i] > max_val) ? in_arr[i] : max_val;
    }}
    out[0] = max_val;
}}
""",
    "sum_to_scalar_device": f"""
{{
    int sum = 0;
    #pragma unroll
    for (int i = 0; i < size; i++){{
        sum += in_arr[i];
    }}
    out = sum;
}}
""",
    "sum_to_address_device": f"""
{{
    int sum = 0;
    #pragma unroll
    for (int i = 0; i < in_size; i++){{
        sum += in_arr[i];
    }}
    out[0] = sum;
}}
""",
    "scan_device": f"""
{{
    int sum = 0;
    #pragma unroll
    for (int i = 0; i < in_size; i++){{
        sum += in_arr[i];
    }}
    out = sum ? 1 : 0;
}}
"""
}

gpu_kernel_code = """
#include <cuda_runtime.h>
#include <thrust/reduce.h>
#include <thrust/functional.h>
#include <thrust/execution_policy.h>
#include <thrust/device_vector.h>

////////////////////////////////////////////////////
// We are running on host, but the data is on device
////////////////////////////////////////////////////

// max zero reduction interface
static void reduce_maxZ_to_address_gpu(const double *__restrict__ d_in, double*__restrict__ d_out, int size, cudaStream_t stream)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Max(nullptr, temp_storage_bytes, d_in, d_out, size, stream);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Max(d_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }

}

static double reduce_maxZ_to_scalar_gpu(const double *__restrict__ d_in, int size, cudaStream_t stream)
{
  cudaError_t err = cudaGetLastError();
if (err != cudaSuccess) {
    printf("2CUDA error: %s\n", cudaGetErrorString(err));
}
  thrust::device_ptr<const double> d_ptr = thrust::device_pointer_cast(d_in);
  double maxval = thrust::reduce(thrust::cuda::par.on(stream), d_ptr, d_ptr + size, 0.0, thrust::maximum<double>());
   err = cudaGetLastError();
  if (err != cudaSuccess) {
      printf("3CUDA error: %s\n", cudaGetErrorString(err));
  }
  return maxval;
}

// sum reduction interface
static void reduce_sum_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, cudaStream_t stream)
{
  void* d_temp_storage = nullptr;
  size_t temp_storage_bytes = 0;

  // Step 1: query temp storage size
  cub::DeviceReduce::Sum(nullptr, temp_storage_bytes, d_in, d_out, size, stream);

  // Step 2: allocate once
  if (temp_storage_bytes != 0) {
    cudaMalloc(&d_temp_storage, temp_storage_bytes);
  }

  // Step 3: call the reduction
  cub::DeviceReduce::Sum(d_temp_storage, temp_storage_bytes, d_in, d_out, size, stream);

  // Cleanup later
  if (temp_storage_bytes != 0) {
    cudaFree(d_temp_storage);
  }
}

static int reduce_sum_to_scalar_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream)
{
  thrust::device_ptr<const int> d_ptr = thrust::device_pointer_cast(d_in);
  int sumval = thrust::reduce(thrust::cuda::par.on(stream), d_ptr, d_ptr + size, 0, thrust::plus<int>());
  return sumval;
}

// scan reduction interface
static int reduce_scan_gpu(const int *__restrict__ d_in, int size, cudaStream_t stream)
{
  return (reduce_sum_to_scalar_gpu(d_in, size, stream) > 0)? 1 : 0;
}

// scan reduction interface
static int reduce_scan_gpu(int d_in, int size, cudaStream_t stream)
{
  return (d_in > 0)? 1 : 0;
}

#include <cstdio>

__device__ __forceinline__ int shared_data_reduce_sum_v2(int* __restrict__ shared_data)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int sum{0};
#pragma unroll
    for (int i{0}; i < NUM_WARPS; ++i)
    {
        sum += shared_data[i];
    }
    return sum;
}

__device__ __forceinline__ int warp_reduce_sum(int val)
{
    constexpr unsigned int FULL_MASK{0xffffffff};
#pragma unroll
    for (int offset{16}; offset > 0; offset /= 2)
    {
        val += __shfl_down_sync(FULL_MASK, val, offset);
    }
    return val;
}

__device__ __forceinline__ int block_reduce_sum_v2(int const* __restrict__ input_data,
                                    int* __restrict__ shared_data,
                                    int num_elements)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int const num_elements_per_thread{(num_elements + NUM_THREADS - 1) / NUM_THREADS};
    int const thread_idx{threadIdx.x};
    int sum{0};
    for (int i{0}; i < num_elements_per_thread; ++i)
    {
        int const offset{thread_idx + i * NUM_THREADS};
        if (offset < num_elements)
        {
            sum += input_data[offset];
        }
    }
    sum = warp_reduce_sum(sum);
    if (threadIdx.x % 32 == 0)
    {
        shared_data[threadIdx.x / 32] = sum;
    }
    __syncthreads();
    int const block_sum{shared_data_reduce_sum_v2(shared_data)};
    return block_sum;
}


static __global__ void batched_reduce_sum_v2(int* __restrict__ output_data,
                                      int const* __restrict__ input_data,
                                      int num_elements_per_batch)
{
    constexpr int NUM_THREADS = 1024;
    constexpr int NUM_WARPS{NUM_THREADS / 32};
    int const block_idx{blockIdx.x};
    int const thread_idx{threadIdx.x};
    __shared__ int shared_data[NUM_WARPS];
    int const block_sum{block_reduce_sum_v2(
        input_data + block_idx * num_elements_per_batch, shared_data,
        num_elements_per_batch)};
    if (thread_idx == 0)
    {
        output_data[block_idx] = block_sum;
    }
}

static void reduce_segmented_to_address_gpu(const int *__restrict__ d_in, int*__restrict__ d_out, int size, int batch_size, cudaStream_t stream)
{
    /*
    cudaError_t err1 = cudaGetLastError();
    if (err1 != cudaSuccess) {
        printf("0CUDA error: %s\n", cudaGetErrorString(err1));
    }
    */
    void *batched_reduce_sum_v2_args[] = {
        (void *)&d_out,
        (void *)&d_in,
        (void *)&size
    };
    constexpr int NUM_WARPS{1024 / 32};
    /*
    printf("NUM_WARPS: %d\n", NUM_WARPS);
    printf("batch_size: %d\n", batch_size);
    printf("size: %d\n", size);
    */

    cudaError_t err = cudaLaunchKernel(
        (void*)batched_reduce_sum_v2,
        dim3(batch_size, 1, 1),
        dim3(1024, 1, 1),
        (void**)batched_reduce_sum_v2_args,
        0,
        stream
    );
    //if (err != cudaSuccess) {
    //    printf("1CUDA error: %s\n", cudaGetErrorString(err));
    //}
    //DACE_KERNEL_LAUNCH_CHECK(err, "batched_reduce_sum_v2", batch_size, 1, 1, NUM_THREADS, 1, 1);
    //batched_reduce_sum_v2<NUM_THREADS><<<batch_size, NUM_THREADS>>>(d_out, d_in, size);
}
"""

cpu_code = """
// max zero reduction interface
static double reduce_maxZ_to_scalar_cpu(const double *d_in, int size)
{
  double max_val = 0;
#pragma omp parallel for reduction(max : max_val)
  for (int i = 0; i < size; i++)
  {
    max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
  }
  return max_val;
}

static void reduce_maxZ_to_address_cpu(const double *d_in, double* d_out, int size)
{
  double max_val = 0;
#pragma omp parallel for reduction(max : max_val)
  for (int i = 0; i < size; i++)
  {
    max_val = (d_in[i] > max_val) ? d_in[i] : max_val;
  }
  d_out[0] = max_val;
}


// sum reduction interface
static int reduce_sum_to_scalar_cpu(const int *d_in, int size)
{
  int sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; i++){
    sum += d_in[i];
  }
  return sum;
}

static void reduce_sum_to_address_cpu(const int *d_in, int* d_out, int size)
{
  int sum = 0.0;
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < size; i++){
    sum += d_in[i];
  }
  d_out[0] = sum;
}


// scan reduction interface
static int reduce_scan_cpu(const int *d_in, int size)
{
  return reduce_sum_to_scalar_cpu(d_in, size) > 0? 1 : 0;
}

// scan reduction interface
static int reduce_scan_cpu(const int d_in, int size)
{
  return d_in > 0? 1 : 0;
}
"""

@make_properties
class LibNode(CodeLibraryNode):
    code = Property(dtype=str, default="", allow_none=False)

    def __init__(self, name, input_names, output_names, code):
        super().__init__(name=name, input_names=input_names, output_names=output_names)
        self.code = code

    def generate_code(self, inputs, outputs):
        if (
            inputs["in_arr"].storage == dace.StorageType.GPU_Global
            or inputs["in_size"].storage == dace.StorageType.GPU_Shared
        ):
            return f"""
            #define __REDUCE_GPU__
            {self.code}
            #undef __REDUCE_GPU__
            """

        return self.code


def _insert_reduction(
    parent: ControlFlowRegion,
    state: dace.SDFGState,
    in_name: str,
    in_size: str,
    out_name: str,
    type: str,
    in_expr: str = None,
    out_expr: str = None,
    symtype: dace.typeclass = None,
):
    """
    Adds a reduction node to the state after the given state.
    """
    red_state = parent.add_state_after(state)

    # Choose the library node
    red_node = dace.nodes.Tasklet(
        label=f"reduce_{type}",
        inputs=["in_arr", "in_size"],
        outputs=["out"],
        code=f"""
        #ifdef __REDUCE_DEVICE__
          {reduction_code_dict[f"{type}_device"]};
        #elif defined(__REDUCE_GPU__)
          out = reduce_{type}_gpu(in_arr, in_size, __dace_current_stream);
        #else
          out = reduce_{type}_cpu(in_arr, in_size);
        #endif
        """ if "address" not in type else f"""
        #ifdef __REDUCE_DEVICE__
          {reduction_code_dict[f"{type}_device"]}
        #elif defined(__REDUCE_GPU__)
          reduce_{type}_gpu(in_arr, out, in_size, __dace_current_stream);
        #else
          reduce_{type}_cpu(in_arr, out, in_size);
        #endif
        """,
        language=dace.Language.CPP,
    )

    # Route array
    in_expr = in_expr if in_expr is not None else in_name
    in_access = None
    if in_name in parent.sdfg.arrays:
        in_access = red_state.add_read(in_name)
    else:
        in_access_task = red_state.add_tasklet(
            f"read_{in_name}", {}, {"out"}, f"out = {in_name}"
        )
        in_sym = parent.sdfg.symbols[in_name]
        in_access_name, in_arr = red_state.sdfg.add_scalar(
            f"reduce_{type}_in",
            dtype=in_sym.dtype,
            transient=True,
            find_new_name=True,
        )
        in_access = red_state.add_read(in_access_name)
        in_expr = in_access_name if in_expr is in_name else in_expr
        red_state.add_edge(
            in_access_task,
            "out",
            in_access,
            None,
            dace.Memlet.from_array(in_access_name, in_arr),
        )
    red_state.add_edge(in_access, None, red_node, "in_arr", dace.Memlet(in_expr))

    # Route size
    size_task = red_state.add_tasklet(
        f"size_reduce_{type}", {}, {"size"}, f"size = {in_size}"
    )
    size_name, _ = red_state.sdfg.add_scalar(
        f"reduce_{type}_size",
        dtype=dace.int32,
        transient=True,
        find_new_name=True,
    )
    size_access = red_state.add_access(size_name)

    red_state.add_edge(size_task, "size", size_access, None, dace.Memlet(size_name))
    red_state.add_edge(size_access, None, red_node, "in_size", dace.Memlet(size_name))

    # Route output
    if out_expr is None:
        #if "address" not in type:
            arr_name, arr = red_state.sdfg.add_scalar(
                "out_val",
                dtype=symtype,
                transient=True,
                find_new_name=True,
            )
            red_state.add_edge(
                red_node,
                "out",
                red_state.add_write(arr_name),
                None,
                dace.Memlet.from_array(arr_name, arr),
            )
            parent.add_state_after(red_state, assignments={out_name: f"{arr_name}"})
        #else:
        #
    else:
        red_state.add_edge(
            red_node, "out", red_state.add_write(out_name), None, dace.Memlet(out_expr)
        )

    return red_state, red_node


def loop_to_max_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the max loop at the end of the SDFG into a reduction.
    """
    loop_node, _ = find_node_by_name(sdfg, loop_name)
    start = str(loop_analysis.get_init_assignment(loop_node))
    end = str(loop_analysis.get_loop_end(loop_node))
    #print("map reduction clipping", start, end)

    vcfl_name = None
    for name in sdfg.arrays.keys():
        if "vcflmax" in name:
            vcfl_name = name
            break
    assert vcfl_name is not None, "vcflmax not found"

    var_names = list(
        loop_node.nodes()[0].branches[0][0].get_free_symbols() - loop_node.free_symbols
    )
    var_name = None
    if len(var_names) == 1:
        var_name = list(var_names)[0]
    else:
        for name in var_names:
            tmp_call_names = [v for v in var_names if "tmp_call" in v]
            assert len(tmp_call_names) == 1, f"{tmp_call_names} is not a single variable"
            var_name = tmp_call_names[0]
    assert var_name is not None, f"Could not deduce output variable name"
    red_state, red_node = _insert_reduction(
        sdfg,
        loop_node,
        vcfl_name,
        f"({end} + 1 - {start})",
        f"{var_name}",
        "maxZ_to_scalar",
        in_expr=f"{vcfl_name}[{start}-1:{end}-1]",
        symtype=dace.float64,
    )
    red_node._offloadable = False
    red_node._output = "scalar"
    pre_state = sdfg.add_state_before(loop_node)
    post_state = sdfg.add_state_after(loop_node)
    sdfg.remove_node(loop_node)
    sdfg.add_edge(pre_state, post_state, dace.InterstateEdge())
    task, _ = find_node_by_name(sdfg, task_name)
    in_name = list(task.free_symbols)[0]
    out_name = list(task.out_connectors.keys())[0]
    task.code.as_string = f"{out_name} = {in_name}"
    task._offloadable = False
    task._output = "scalar"


def cfl_clipping_to_reduction(sdfg: dace.SDFG, task_name, cond_name, loop_name):
    """
    Turns the cfl_clipping scan/sum into a reduction.
    """
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    cond_block, parent = find_node_by_name(sdfg, cond_name)
    parent.remove_node(cond_block)
    loop, parent = find_node_by_name(sdfg, loop_name)
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))
    #print("cfl clipping", start, end)

    outer_loop = parent
    outer_it_var = outer_loop.loop_variable

    from utils.move_scalar_to_array import move_scalar_to_array
    dst_arr_name = "out_val_0"
    if "out_val_0" not in sdfg.arrays:
        sdfg.add_array(
            "out_val_0",
            shape=[1],
            dtype=dace.int32,
            transient=True,
            find_new_name=False,
        )
    #move_scalar_to_array(sdfg, dst_arr_name)
    red_state, red_node = _insert_reduction(
        parent,
        loop,
        "cfl_clipping",
        f"({end} + 1 - {start})",
        "out_val_0",
        "sum_to_address",
        in_expr=f"cfl_clipping[{start}-1:{end}-1,{outer_it_var}-1]",
        out_expr=f"out_val_0[0:0]",
        symtype=dace.int32,
    )
    red_node._offloadable = True
    red_node._output = "array"

    # Replace conditional clip_count with out_val_0[0]
    succ = parent.successors(red_state)[0]
    assert isinstance(succ, ConditionalBlock)

    succ.replace_meta_accesses({"clip_count": "out_val_0[0]"})

    # Change interstate edge
    for oe in red_state.parent_graph.out_edges(red_state):
        if oe.data is not None:
            if oe.data.assignments is not None:
                for k, v in oe.data.assignments.items():
                    if v == "out_val":
                        oe.data.assignments[k] = "out_val[0]"
    sdfg.validate()

    task._offloadable = True
    task._output = "array"

def maxvcfl_to_reduction(sdfg: dace.SDFG, task_name, loop_name):
    """
    Turns the maxvcfl max into a reduction.
    """
    task, parent = find_node_by_name(sdfg, task_name, skip=1)
    tmp_call = "tmp_call_8_0_in"
    assert task.code.as_string == f"maxvcfl_out = max(maxvcfl_0_in, {tmp_call})", task.code.as_string
    task.code.as_string = f"maxvcfl_out = {tmp_call}"
    task.remove_in_connector("maxvcfl_0_in")
    for pred in parent.predecessors(task):
        if pred.label == "maxvcfl":
            parent.remove_node(pred)
    parent.remove_node(parent.successors(task)[0])

    loop, loop_P = find_node_by_name(sdfg, loop_name)

    inner_loop = parent.parent_graph.parent_graph.parent_graph
    assert isinstance(inner_loop, LoopRegion)
    ol_it_name = loop.loop_variable
    il_it_name = inner_loop.loop_variable

    ol_start = str(loop_analysis.get_init_assignment(loop))
    ol_end = str(loop_analysis.get_loop_end(loop))
    il_start = str(loop_analysis.get_init_assignment(inner_loop))
    il_end = str(loop_analysis.get_loop_end(inner_loop))
    #print("ol il", ol_start, ol_end)

    # The sizes need to be symbolic for dace to allocate the array correctly
    ol_size_sym = parent.sdfg.add_symbol(
        "ol_size", stype=dace.dtypes.int32, find_new_name=True
    )
    #il_size_sym = parent.sdfg.add_symbol(
    #    "il_size", stype=dace.dtypes.int64, find_new_name=True
    #)
    sdfg.add_state_after(
        sdfg.start_state,
        assignments={
            f"{ol_size_sym}": f"{ol_end} + 1",
            #f"{il_size_sym}": f"__CG_global_data__m_nproma",
        },
    )

    # Ensure column-major order (canonical layout for all arrays)
    arr_name, arr = parent.sdfg.add_array(
        "maxvcfl_arr",
        shape=[f"tmp_struct_symbol_4", f"{ol_size_sym}"],
        strides=[1, dace.symbolic.SymExpr(f"tmp_struct_symbol_4")],
        dtype=dace.float64,
        transient=True,
        find_new_name=True,
    )
    arr_acc = parent.add_write(arr_name)

    parent.add_edge(
        task,
        "maxvcfl_out",
        arr_acc,
        None,
        dace.Memlet(f"{arr_name}[{il_it_name}-1,{ol_it_name}-1]"),
    )

    red_state, red_node = _insert_reduction(
        loop_P,
        loop,
        "maxvcfl_arr",
        f"({il_end} + 1 - {il_start}) * (87)",
        "maxvcfl",
        "maxZ_to_scalar",
        in_expr=f"maxvcfl_arr[{il_start}-1:{il_end}-1,0:87]",
        out_expr="maxvcfl[0]",
        symtype=dace.float64,
    )
    red_node._offloadable = False
    red_node._output = "scalar"

def tmp_call_13_to_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the tmp_call_13 scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, loop_name)
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))
    #print("tmp_call_13", start, end)

    outer_loop = parent
    outer_it_var = outer_loop.loop_variable

    red_state, red_node = _insert_reduction(
        parent,
        loop,
        "levmask",
        f"({end} + 1 - {start})",
        "levelmask",
        "scan",
        in_expr=f"levmask[{start}-1:{end}-1,{outer_it_var}-1]",
        out_expr=f"levelmask[{outer_it_var}-1]",
        symtype=dace.int32,
    )
    pre_state = parent.add_state_before(loop)
    post_state = parent.add_state_after(loop)
    parent.remove_node(loop)
    parent.add_edge(pre_state, post_state, dace.InterstateEdge())
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)
    red_node._offloadable = True
    red_node._output = "array"

def levmask_to_reduction(sdfg: dace.SDFG, loop_name, task_name):
    """
    Turns the levmask scan into a reduction.
    """
    loop, parent = find_node_by_name(sdfg, loop_name)
    prestate = parent.add_state_before(loop)
    start = str(loop_analysis.get_init_assignment(loop))
    end = str(loop_analysis.get_loop_end(loop))
    #print("levmask", start, end)

    outer_loop = parent.parent_graph.parent_graph
    assert isinstance(outer_loop, LoopRegion)
    outer_it_var = outer_loop.loop_variable

    outer_outer_loop = outer_loop.parent_graph
    assert isinstance(outer_outer_loop, LoopRegion)
    outer_outer_it_var = outer_outer_loop.loop_variable

    _insert_reduction(
        parent,
        prestate,
        "cfl_clipping",
        f"1",
        "levmask",
        "scan",
        in_expr=f"cfl_clipping[{outer_outer_it_var}-1,{outer_it_var}-1]",
        out_expr=f"levmask[{outer_outer_it_var}-1,{outer_it_var}-1]",
        symtype=dace.int32,
    )
    task, parent = find_node_by_name(sdfg, task_name)
    parent.remove_node(parent.successors(task)[0])
    parent.remove_node(task)


def _demote_vcflmax(sdfg: dace.SDFG):
    """
    Demotes the vcflmax symbol to a scalar.
    vcflmax is only used in interstate edges, so we only check interstate edges and replace them.
    """
    vcfl_name, _ = sdfg.add_array(
        "vcflmax",
        shape=[
            1,
        ],
        dtype=sdfg.symbols["vcflmax"],
        transient=True,
        find_new_name=True,
    )
    replaced_write = False
    replaced_read = False
    for edge, parent in sdfg.all_edges_recursive():
        if not isinstance(edge.data, dace.sdfg.InterstateEdge):
            continue
        if "vcflmax" in edge.data.assignments.keys():
            assert (
                not replaced_write
            ), "TODO: vcflmax is assigned in multiple interstate edges"
            del edge.data.assignments["vcflmax"]

            vstate = parent.add_state_after(edge.src, "vcflmax_state")
            rnode = vstate.add_read("maxvcfl")
            wnode = vstate.add_write(vcfl_name)
            vstate.add_edge(
                rnode,
                None,
                wnode,
                None,
                dace.Memlet.from_array("maxvcfl", sdfg.arrays["maxvcfl"]),
            )
            replaced_write = True
        if "vcflmax" in edge.data.assignments.values():
            assert (
                not replaced_read
            ), "TODO: vcflmax is read in multiple interstate edges"
            edge.data.replace("vcflmax", vcfl_name)
            replaced_read = True

    sdfg.remove_symbol("vcflmax")


def add_all_reductions(sdfg: dace.SDFG):
    # Make sure vcflmax is not a symbol
    #if "vcflmax" in sdfg.symbols:
    #    import warnings
    #
    #    warnings.warn("vcflmax is a symbol, demoting to a scalar")
    #    _demote_vcflmax(sdfg)
    assert "vcflmax" not in sdfg.symbols, "vcflmax is a symbol, demoting to a scalar"

    sdfg.append_global_code(
        cpp_code=gpu_kernel_code,
        location="cuda"
    )
    sdfg.append_global_code(
        cpp_code=cpu_code,
        location="frame"
    )

    # We assume the array names and iteration variable names never change
    if "nproma32" in sdfg.name:
        loop_to_max_reduction(sdfg, f"FOR_l_568_c_568", "T_l568_c568")
        cfl_clipping_to_reduction(
            sdfg, "T_l467_c467", "Conditional_l_467_c_467", f"FOR_l_465_c_465"
        )
        maxvcfl_to_reduction(sdfg, "T_l474_c474", f"FOR_l_463_c_463")
        tmp_call_13_to_reduction(sdfg, f"FOR_l_516_c_516", "T_l516_c516")
        levmask_to_reduction(sdfg, f"FOR_l_470_c_470", "T_l472_c472")

    elif "nproma20480" in sdfg.name:
        loop_to_max_reduction(sdfg, f"FOR_l_652_c_652", "T_l652_c652")
        cfl_clipping_to_reduction(
            sdfg, "T_l551_c551", "Conditional_l_551_c_551", "FOR_l_549_c_549"
        )
        maxvcfl_to_reduction(sdfg, "T_l558_c558", f"FOR_l_547_c_547")
        tmp_call_13_to_reduction(sdfg, f"FOR_l_600_c_600", "T_l600_c600")
        levmask_to_reduction(sdfg, f"FOR_l_554_c_554", "T_l556_c556")
    elif "no_nproma" in sdfg.name:
        # Final reduction over nblocks, this will be on CPU -> write to scalar
        loop_to_max_reduction(sdfg, f"FOR_l_652_c_652", "T_l652_c652")
        # Will be used on GPU next kernel, write to array
        cfl_clipping_to_reduction(
            sdfg, "T_l551_c551", "Conditional_l_551_c_551", "FOR_l_549_c_549"
        )

        # vcflmax will be kept on the CPU so this should write to a scalar
        maxvcfl_to_reduction(sdfg, "T_l558_c558", f"FOR_l_547_c_547")

        tmp_call_13_to_reduction(sdfg, f"FOR_l_600_c_600", "T_l600_c600")

        # This is a scan of size 1 for compatibility with future transformations
        levmask_to_reduction(sdfg, f"FOR_l_554_c_554", "T_l556_c556")

    else:
        raise ValueError("Unknown NPROMA size")
