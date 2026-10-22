# asc::std::empty

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

`asc::std::empty` determines whether the range contains no elements.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class Cont> constexpr auto empty(const Cont& c) noexcept(noexcept(c.empty())) -> decltype(c.empty());
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T, size_t Sz> constexpr bool empty(const T (&c)[Sz]) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Cont` | The type of the container being queried; it must provide the size, empty, or data member invoked by this overload. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input | Reference to the object used by "determines whether the range contains no elements"; the referenced object must remain valid for the duration of the call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the built-in array. |
| `Sz` | The number of elements of the built-in array in this dimension, deduced from the array argument. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input | Reference to the object used by "determines whether the range contains no elements"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `decltype(c.empty())` | Returns `true` if the input range contains no elements, otherwise `false`. |
| Prototype 2 | `bool` | Returns `true` if the object contains no elements, otherwise `false`. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    return !asc::std::empty(values);
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
