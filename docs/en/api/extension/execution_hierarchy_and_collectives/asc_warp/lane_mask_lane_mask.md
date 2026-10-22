# asc::lane_mask::lane_mask

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

`asc::lane_mask::lane_mask` initializes an `asc::lane_mask` object with the parameters provided by the caller.

## Function Prototype

Member of: [`asc::lane_mask`](lane_mask.md).

```cpp
// Excerpt of the declaration inside class asc::lane_mask; template parameters and other members are provided by the enclosing class.
constexpr explicit lane_mask(unsigned int value = 0) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Raw 32-bit lane mask value (unsigned int; the default 0 is the empty mask): bit i (counting from 0) set to 1 indicates that lane i belongs to the set. |

## Return Value

No return value.

## Constraints

- Construction, observation, and bitwise operations on mask values are available on Host, in AI Core SIMD programming, and in AI Core SIMT programming.
- Each bit corresponds to a lane numbered 0-31 in the warp; 1 indicates that the lane is selected.
- The mask value itself performs no synchronization; when using it in a warp operation, the participant rendezvous requirements of that operation must also be satisfied.

## Example

The following Host example checks bitwise operations and the returned objects with concrete masks; mask value operations themselves perform no warp synchronization.

```cpp
#include <asc/warp>
bool example()
{
    asc::lane_mask empty;
    asc::lane_mask selected(5u);
    return empty.value() == 0u && selected.value() == 5u;
}
```

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
