# asc::std::begin

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

`asc::std::begin` obtains the start iterator of the range.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

`asc::std::begin` is a callable object, invoked as `asc::std::begin(range)`. The following queries the type of the public object and lists the summary of its call operators.

```cpp
namespace asc::std {
// Queries the type of the public object; the object and its call operators are provided by the header.
using begin_object_type = decltype(::asc::std::begin);
}
```

### Prototype 1

```cpp
// Excerpt of the declaration inside the callable object's type.
template<class C>
constexpr auto operator()(C& c) const
    noexcept(noexcept(c.begin())) -> decltype(c.begin());
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the callable object's type.
template<class C>
constexpr auto operator()(const C& c) const
    noexcept(noexcept(c.begin())) -> decltype(c.begin());
```

### Prototype 3

```cpp
// Excerpt of the declaration inside the callable object's type.
template<class T, size_t N>
constexpr T* operator()(T (&array)[N]) const noexcept;
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
| `c` | Input/Output | Reference to the object used by "obtains the start iterator of the range"; the referenced object must remain valid for the duration of the call. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `C` | The type of the array or container being queried; it must provide the corresponding range access operations. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `c` | Input | Reference to the object used by "obtains the start iterator of the range"; the referenced object must remain valid for the duration of the call. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the built-in array. |
| `N` | The type or compile-time value representing the element count, dimension, bit width, or index, as determined by the declaration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `array` | Input/Output | Reference to the object used by "obtains the start iterator of the range"; the referenced object must remain valid for the duration of the call. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `decltype(c.begin())` | Returns the start iterator of the range. |
| Prototype 2 | `decltype(c.begin())` | Returns the start iterator of the range. |
| Prototype 3 | `T*` | Returns the start iterator of the range. |

## Constraints

- The container form requires the corresponding const or non-const member access expression to be valid; the built-in array form preserves the element type and const qualification.
- The iterator returned by the object does not own the range; the underlying container or array must remain valid while it is in use.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto first = asc::std::begin(values);
    return first == values && *first == 1;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
