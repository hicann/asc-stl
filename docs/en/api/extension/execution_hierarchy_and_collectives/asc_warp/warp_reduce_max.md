# asc::warp_reduce_max

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

`asc::warp_reduce_max` returns the maximum of the values of the participating lanes in the current warp.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
float warp_reduce_max(float value) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
int warp_reduce_max(int value) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
unsigned int warp_reduce_max(unsigned int value) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the reduction: returns the maximum of this value across all lanes of the warp. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the reduction: returns the maximum of this value across all lanes of the warp. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The input value this lane contributes to the reduction: returns the maximum of this value across all lanes of the warp. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `float` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |
| Prototype 2 | `int` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |
| Prototype 3 | `unsigned int` | Returns the result of reducing the participating threads or the contiguous range according to the interface name. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All participating active threads must call it in converged control flow.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/warp>

__aicore__ decltype(auto) example(float value)
{
    return asc::warp_reduce_max(value);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source:

- [CMakeLists.txt](../../../../../zh/examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../../zh/examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../../zh/examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../../zh/examples/warp_collectives/main.cpp)

## Related APIs

- [API list for this header](asc_warp.md)
