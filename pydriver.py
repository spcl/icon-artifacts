import pycuda.driver as cuda
import pycuda.autoinit

try:
    ptr = cuda.pagelocked_empty(1024, dtype='float32')  # Try allocating pinned memory
    print("cudaMallocHost (pinned memory) is supported.")
except cuda.MemoryError:
    print("cudaMallocHost is not supported.")
except Exception as e:
    print(f"Error: {e}")


try:
    ptr = cuda.managed_zeros(1024, dtype="float32")  # Try allocating pinned memory
    print("cudaMallocManged(pinned memory) is supported.")
except cuda.MemoryError:
    print("cudaMallocManaged is not supported.")
except Exception as e:
    print(f"Error: {e}")
