# asc::warp_match_any

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

`asc::warp_match_any` returns the mask of participating lanes whose values equal the current lane's value.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
asc::lane_mask warp_match_any(bool value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
asc::lane_mask warp_match_any(float value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
asc::lane_mask warp_match_any(int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 4

```cpp
namespace asc {
asc::lane_mask warp_match_any(long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 5

```cpp
namespace asc {
asc::lane_mask warp_match_any(unsigned int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 6

```cpp
namespace asc {
asc::lane_mask warp_match_any(unsigned long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: the lanes set in the returned mask have this value bitwise equal to the current lane's. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |
| Prototype 2 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |
| Prototype 3 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |
| Prototype 4 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |
| Prototype 5 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |
| Prototype 6 | `asc::lane_mask` | Returns the mask of participating lanes whose values equal the current lane's value. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All participating active threads must call it in converged control flow.
- float keys are matched bit by bit by their object representation.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/warp>

__aicore__ decltype(auto) example(bool value, asc::lane_mask participants = asc::lane_mask::all())
{
    return asc::warp_match_any(value, participants);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source:

- [CMakeLists.txt](../../../../../../examples/extension/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../../../examples/extension/warp_collectives/warp_example.h)
- [kernel.asc](../../../../../../examples/extension/warp_collectives/kernel.asc)
- [main.cpp](../../../../../../examples/extension/warp_collectives/main.cpp)

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
