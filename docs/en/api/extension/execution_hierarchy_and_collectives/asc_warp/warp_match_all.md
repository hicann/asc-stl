# asc::warp_match_all

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

`asc::warp_match_all` determines whether the values provided by the participating lanes are all equal.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
bool warp_match_all(bool value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
bool warp_match_all(float value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
bool warp_match_all(int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 4

```cpp
namespace asc {
bool warp_match_all(long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 5

```cpp
namespace asc {
bool warp_match_all(unsigned int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### Prototype 6

```cpp
namespace asc {
bool warp_match_all(unsigned long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the match: returns true when this value is bitwise equal across all lanes in participants. |
| `participants` | Input | Lane set mask for the match (lane_mask, bit i corresponds to lane i, default lane_mask::all()): only lanes in the set participate in the comparison. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 2 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 3 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 4 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 5 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 6 | `bool` | Returns `true` when the condition holds, otherwise `false`. |

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
    return asc::warp_match_all(value, participants);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source:

- [CMakeLists.txt](../../../../../zh/examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../../zh/examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../../zh/examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../../zh/examples/warp_collectives/main.cpp)

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
