# asc::std::kill_dependency

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

Header: `<asc/std/atomic>`.

`asc::std::kill_dependency` removes the dependency-chain marking of a value without changing the value.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
template<class T> constexpr T kill_dependency(T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the input value and the return value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value obtained from the dependency chain; the value is returned unchanged and its dependency ordering relationship with previous evaluations is cut off. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the same value as the input while removing the dependency-chain marking of the expression. |

## Constraints

- constexpr/noexcept.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet uses a concrete integer atomic object; device-side objects must be located in accessible global memory.

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    return asc::std::kill_dependency(1);
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
