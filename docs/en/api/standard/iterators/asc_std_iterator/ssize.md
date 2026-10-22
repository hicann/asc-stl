# asc::std::ssize

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

Header: `<asc/std/iterator>`.

`asc::std::ssize` returns the number of elements in a range as a signed integer.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class Cont> constexpr auto ssize(const Cont& value) noexcept(noexcept(static_cast<common_type_t<ptrdiff_t, make_signed_t<decltype(value.size())>>>(value.size()))) -> common_type_t<ptrdiff_t, make_signed_t<decltype(value.size())>>;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T, ptrdiff_t Sz> constexpr ptrdiff_t ssize(const T (&value)[Sz]) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Cont` | The container type; it must provide a size() member. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The container whose element count is measured; returns the signed form of its size(). |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the array. |
| `Sz` | The array length, a compile-time constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The array whose element count is measured; returns its length Sz (as a signed integer). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `common_type_t<ptrdiff_t, make_signed_t<decltype(value.size())>>` | Returns the number of elements in the range. |
| Prototype 2 | `ptrdiff_t` | Returns the number of elements in the range. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host snippet demonstrates the call with a concrete array or an explicit container; the iterator must remain within the valid range.

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::ssize(values);
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
