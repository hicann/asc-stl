# asc::std::addressof

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

Header: `<asc/std/memory>`.

`asc::std::addressof` obtains the actual address of an object without invoking an overloaded address-of operator.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

```cpp
namespace asc::std {
template<typename T> [[nodiscard]] constexpr T* addressof(T& value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the object whose actual address is to be obtained. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The object (lvalue) whose actual address is to be obtained; even if its type overloads operator&, that overload is not invoked. |

## Return Value

| Return type | Description |
| --- | --- |
| `T *` | Returns the actual address of the object without invoking an overloaded address-of operator. |

## Constraints

- Raw pointers and user-defined fancy pointers are supported; the interface itself allocates no memory.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/memory>

template <typename T>
decltype(auto) example(T & value)
{
    return asc::std::addressof(value);
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [pointer_alignment.cpp](../../../../../zh/examples/pointer_alignment.cpp).

## Related APIs

- [API list for this header](asc_std_memory.md)
