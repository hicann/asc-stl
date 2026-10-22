# asc::lane_mask::`operator!=`

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

`asc::lane_mask::operator!=` compares whether two lane masks differ.

## Function Prototype

Member of: [`asc::lane_mask`](lane_mask.md).

```cpp
// Excerpt of the declaration inside class asc::lane_mask; template parameters and other members are provided by the enclosing class.
constexpr bool operator!=(asc::lane_mask other) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The other operand of the comparison; this comparison does not modify the objects. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

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
    asc::lane_mask left(3u);
    asc::lane_mask right(5u);
    return left != right && !(left != asc::lane_mask(3u));
}
```

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
