# asc::std::minmax

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

Header: `<asc/std/algorithm>`.

`asc::std::minmax` returns the minimum and maximum at the same time; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class T, class Compare>
[[nodiscard]] constexpr pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] constexpr pair<const T&, const T&> minmax(const T& a, const T& b);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the input range elements or of the values participating in the operation. |
| `Compare` | Comparison object type that defines the ordering of the elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Object reference used for "returning the minimum and maximum at the same time"; the referenced object must remain valid during the call. |
| `b` | Input | Object reference used for "returning the minimum and maximum at the same time"; the referenced object must remain valid during the call. |
| `comp` | Input | Comparison object used to determine the ordering of the elements. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the input range elements or of the values participating in the operation. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Object reference used for "returning the minimum and maximum at the same time"; the referenced object must remain valid during the call. |
| `b` | Input | Object reference used for "returning the minimum and maximum at the same time"; the referenced object must remain valid during the call. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `pair<const T &, const T &>` | Returns the minimum and maximum. |
| Prototype 2 | `pair<const T &, const T &>` | Returns the minimum and maximum. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::minmax(values[0], values[1]);
    return &result.first == values && &result.second == values + 1;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
