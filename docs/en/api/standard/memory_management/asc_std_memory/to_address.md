# asc::std::to_address

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

`asc::std::to_address` converts a raw or custom pointer to the underlying raw address.

Standard semantics reference: [cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class Pointer> constexpr auto to_address(const Pointer& pointer) noexcept -> decltype(::asc::std::__to_address(pointer));
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> constexpr T* to_address(T* pointer) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Pointer` | The pointer or pointer-like type whose underlying raw address is to be obtained. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Provides the object reference used by "converting a raw or custom pointer to the underlying raw address"; the referenced object must be valid for the duration of the call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of object being constructed, destroyed, or managed. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The pointer or pointer-like object whose raw object address is to be obtained; does not dereference the pointed-to object and does not transfer its ownership. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the raw address corresponding to the input pointer or pointer-like object. |
| Prototype 2 | `T*` | Returns the raw address corresponding to the input pointer or pointer-like object. |

## Constraints

- Raw pointers and user-defined fancy pointers are supported; the interface itself allocates no memory.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/memory>

template <class Pointer>
decltype(auto) example(const Pointer & pointer)
{
    return asc::std::to_address(pointer);
}
```

The corresponding complete project uses `C++17` and has been verified by Host compilation and execution.

Complete example source: [pointer_alignment.cpp](../../../../../zh/examples/pointer_alignment.cpp).

## Related APIs

- [API list for this header](asc_std_memory.md)
