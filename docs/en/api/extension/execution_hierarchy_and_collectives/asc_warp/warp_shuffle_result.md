# asc::warp_shuffle_result

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

Header: `<asc/warp>`.

`asc::warp_shuffle_result` holds both the data obtained by the warp shuffle and whether the source lane is valid.

This interface is available in AI Core SIMT programming.

## Declaration

```cpp
namespace asc {
template<class T> struct warp_shuffle_result;
} // namespace asc
```

## Constraints

- T can only be int, unsigned int, float, long long, or unsigned long long.

## Example

Launched with 1 block and 32 threads, all lanes execute this snippet in converged control flow. output points to 32 GM elements; after synchronization completes, each element should be 1.

```cpp
#include <asc/warp>

__global__ void example(unsigned int* output)
{
    const unsigned int lane = asc::lane_id();
    const asc::warp_shuffle_result<unsigned int> result = asc::warp_shuffle_idx<32>(lane, 0, asc::lane_mask::all());
    output[lane] = result.valid && result.data == 0;
}
```

For the complete project and run steps, see the [warp_collectives example](../../../../../../examples/extension/warp_collectives/README_en.md).

## Related APIs

- [API list for this header](asc_warp.md)
