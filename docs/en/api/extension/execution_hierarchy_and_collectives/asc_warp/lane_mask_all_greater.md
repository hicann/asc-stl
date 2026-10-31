# asc::lane_mask::all_greater

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

`asc::lane_mask::all_greater` returns the mask of lanes whose index is greater than the current lane.

## Function Prototype

Member of: [`asc::lane_mask`](lane_mask.md).

```cpp
// Excerpt of the declaration inside class asc::lane_mask; template parameters and other members are provided by the enclosing class.
static asc::lane_mask all_greater() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::lane_mask` | Returns the mask of lanes whose index is greater than the current lane. |

## Constraints

- The relative-position set is intersected with the set of lanes active at this call; inactive lanes in divergent control flow are not included merely because of their index. Only when the whole warp is converged does it equal the relative mask of all 32 indices.

- Can only be called in AI Core SIMT programming.
- Each bit corresponds to a lane numbered 0-31 in the warp; 1 indicates that the lane is selected.
- The current warp is queried only in AI Core SIMT programming; the set of active bits is determined at the point of this call.
- The mask value itself performs no synchronization; when using it in a warp operation, the participant rendezvous requirements of that operation must also be satisfied.

## Example

Launched with 1 block and 32 threads, all lanes execute this snippet in converged control flow. output points to 32 GM elements; after synchronization completes, each element should be 1.

```cpp
#include <asc/warp>

__global__ void example(unsigned int* output)
{
    const unsigned int lane = asc::lane_id();
    const asc::lane_mask mask = asc::lane_mask::all_greater();
    output[lane] = mask.value() == ((lane == 31U ? 0U : 0xffffffffU << (lane + 1U)));
}
```

For the complete project and run steps, see the [warp_collectives example](../../../../../../examples/extension/warp_collectives/README_en.md).

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
