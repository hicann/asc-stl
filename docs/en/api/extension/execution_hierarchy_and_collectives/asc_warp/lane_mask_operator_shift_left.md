# asc::lane_mask::`operator<<`

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

`asc::lane_mask::operator<<` returns the result of shifting the lane mask left by the specified number of positions.

## Function Prototype

Member of: [`asc::lane_mask`](lane_mask.md).

```cpp
// Excerpt of the declaration inside class asc::lane_mask; template parameters and other members are provided by the enclosing class.
constexpr asc::lane_mask operator<<(int shift) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `shift` | Input | Number of positions to shift left (0~31): mask bits move toward higher bit positions with low bits filled with 0; returns a new lane_mask and does not modify this object. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::lane_mask` | Returns the result of shifting the lane mask left by the specified number of positions. |

## Constraints

- shift must be within [0, 31]; negative shifts or shifts of 32 or greater are not valid calls.

- Construction, observation, and bitwise operations on mask values are available on Host, in AI Core SIMD programming, and in AI Core SIMT programming.
- Each bit corresponds to a lane numbered 0-31 in the warp; 1 indicates that the lane is selected.
- shift must be within [0, 31]; this value operation performs no warp rendezvous or memory synchronization.

## Example

The following Host example checks bitwise operations and the returned objects with concrete masks; mask value operations themselves perform no warp synchronization.

```cpp
#include <asc/warp>
bool example()
{
    asc::lane_mask left(3u);
    const auto result = left << 1;
    return result.value() == 6u && left.value() == 3u;
}
```

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
