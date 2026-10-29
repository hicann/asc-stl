# asc::thread_count

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/hierarchy>`.

`asc::thread_count` returns the total number of threads in the current block, blockDim.x*blockDim.y*blockDim.z.

## Function Prototype

```cpp
namespace asc {
unsigned long long thread_count() noexcept;
}  // namespace asc
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned long long` | Returns the number of units in the enclosing execution hierarchy level. |

## Constraints

- Can only be called in AI Core SIMT programming.
- The query must be performed inside an executing AI Core SIMT kernel; the result is taken from the current launch configuration, and this function performs no thread synchronization.

## Example

For a SIMT launch with Grid=(2,3,4) and Block=(8,4,2), this kernel writes each thread's query result to a separate location. The caller must allocate valid GM output for at least 1536 unsigned long long values and read it back after kernel completion. Every entry is 64. The documentation gate checks actual SIMT compilation; it does not establish successful NPU execution.

```cpp
#include <asc/hierarchy>

__global__ void example(unsigned long long* output)
{
    const unsigned long long local = threadIdx.x +
        static_cast<unsigned long long>(blockDim.x) * (threadIdx.y + blockDim.y * threadIdx.z);
    const unsigned long long block = blockIdx.x +
        static_cast<unsigned long long>(gridDim.x) * (blockIdx.y + gridDim.y * blockIdx.z);
    const unsigned long long threads = static_cast<unsigned long long>(blockDim.x) * blockDim.y * blockDim.z;
    const unsigned long long offset = block * threads + local;
    output[offset] = asc::thread_count();
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
