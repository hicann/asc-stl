# asc::std::rend

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

`asc::std::rend` obtains the past-the-end iterator of the reversed range.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class C> constexpr auto rend(C& c) noexcept(noexcept(c.rend())) -> decltype(c.rend());
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class C> constexpr auto rend(const C& c) noexcept(noexcept(c.rend())) -> decltype(c.rend());
} // namespace asc::std
```

### Prototype 3

```cpp
namespace asc::std {
template<class T, asc::std::size_t N> constexpr asc::std::reverse_iterator<T*> rend(T (&array)[N]) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `C` | The type of the array or container being queried; it must provide the corresponding range access operations. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input/Output | The object reference used by "obtains the past-the-end iterator of the reversed range"; the referenced object must remain valid during the call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `C` | The type of the array or container being queried; it must provide the corresponding range access operations. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input | The object reference used by "obtains the past-the-end iterator of the reversed range"; the referenced object must remain valid during the call. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the built-in array. |
| `N` | The type or compile-time value representing the element count, dimension, bit width, or index, as determined by the declaration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `array` | Input/Output | The object reference used by "obtains the past-the-end iterator of the reversed range"; the referenced object must remain valid during the call. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `decltype(c.rend())` | Returns the past-the-end iterator of the reversed range. |
| Prototype 2 | `decltype(c.rend())` | Returns the past-the-end iterator of the reversed range. |
| Prototype 3 | `asc::std::reverse_iterator<T*>` | Returns the past-the-end iterator of the reversed range. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto last = asc::std::rend(values);
    return last.base() == values && last - asc::std::rbegin(values) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
