# asc::std::tuple::tuple

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

Header: `<asc/std/tuple>`.

`asc::std::tuple::tuple` initializes a `tuple` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

The following is a **call-form summary** inside the owning class. The SFINAE selection parameters used by the implementation are omitted; the implicit and explicit forms of the same shape are selected by the constructibility and convertibility conditions below, and the summary must not be copied as a set of unconditional overload definitions.

```cpp
constexpr tuple() = default;
```

```cpp
tuple(const tuple&) = default;
```

```cpp
tuple(tuple&&) = default;
```

```cpp
constexpr tuple(const Types&... values);
```

```cpp
constexpr explicit tuple(const Types&... values);
```

```cpp
template <class... Values>
constexpr tuple(Values&&... values);
```

```cpp
template <class... Values>
constexpr explicit tuple(Values&&... values);
```

```cpp
template <class... UTypes>
constexpr tuple(const tuple<UTypes...>& other);
```

```cpp
template <class... UTypes>
constexpr explicit tuple(const tuple<UTypes...>& other);
```

```cpp
template <class... UTypes>
constexpr tuple(tuple<UTypes...>&& other);
```

```cpp
template <class... UTypes>
constexpr explicit tuple(tuple<UTypes...>&& other);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const Types&... values);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple& other);
```

```cpp
template <class Alloc>
constexpr tuple(allocator_arg_t, const Alloc& alloc, tuple&& other);
```

```cpp
template <class Alloc, class... UTypes>
constexpr tuple(allocator_arg_t, const Alloc& alloc, const tuple<UTypes...>& other);
```

## Parameters

**Template Parameters**

`Types...` are the element types of the owning tuple; Values... and UTypes... denote the element-wise argument types and the source tuple element types respectively, and Alloc is the allocator type.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `values...` | Input/Output (movable source) | Constructs each element according to the corresponding value category; the const reference form is read-only. |
| `other` | Input/Output (movable source) | The source tuple; copied from a const reference, and the rvalue form may be moved. |
| `alloc` | Input | The allocator used by the allocator_arg forms; it participates in construction according to each element's uses_allocator rules. |

## Return Value

No return value.

## Constraints

- The const Types&... element construction is for non-empty tuples only. The implicit and explicit summaries of the same shape are selected respectively by the element-wise implicitly convertible condition and the at-least-one-explicit-conversion condition.

- The number of arguments must match the number of Types... and each element must be constructible from the corresponding source; the non-explicit form is used when all corresponding conversions can be done implicitly, otherwise the explicit form is used. Heterogeneous tuple conversion also excludes cases that should be handled by the single-element construction or the copy/move forms. The allocator_arg forms pass the allocator according to each element's uses_allocator rules; whether construction, copying, or user element operations allocate is determined by those operations.
- User-provided construction, allocation, and callable operations must be valid at the selected execution location; Device instances must suit the non-throwing target environment.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <memory>
#include <asc/std/tuple>

bool example()
{
    asc::std::tuple<int, int> values(2, 3);
    asc::std::tuple<long, long> converted = values;
    ::std::allocator<int> allocator;
    asc::std::tuple<int, int> allocated(asc::std::allocator_arg, allocator, 4, 5);
    return asc::std::get<0>(converted) == 2 && asc::std::get<1>(allocated) == 5;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
