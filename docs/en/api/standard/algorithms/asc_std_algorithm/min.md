# asc::std::min

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

`asc::std::min` returns a reference to the smaller value under the comparison relation; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template <class T, class Compare>
[[nodiscard]] constexpr const T& min(const T& left, const T& right, Compare compare);
}  // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] constexpr const T& min(const T& left, const T& right);
}  // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the operands compared to obtain the smaller value. |
| `Compare` | Comparator type; invoked in the form compare(a, b), returns bool. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand compared to obtain the smaller value; this operand is returned when it is equivalent to right. |
| `right` | Input | Right operand compared to obtain the smaller value. |
| `compare` | Input | Comparator; invoked in the form compare(a, b), returns bool, where true means a is less than b; returns the smaller of the two, and returns left when they are equivalent. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of the operands compared to obtain the smaller value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand compared to obtain the smaller value; this operand is returned when it is equivalent to right. |
| `right` | Input | Right operand compared to obtain the smaller value. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const T &` | Returns a reference to the smaller value. |
| Prototype 2 | `const T &` | Returns a reference to the smaller value. |

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.

## Example

The following Host example checks the result and output while the local range is still valid; the function returns a boolean value that can be evaluated independently.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    const auto& result = asc::std::min(values[0], values[1]);
    return &result == values && result == 1;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
