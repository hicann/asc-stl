# asc::std::clamp

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

`asc::std::clamp` confines `value` to the closed range determined by `lower` and `upper`, available since C++17. It returns `lower` when `value` is before the lower bound, `upper` when `value` is after the upper bound, and `value` otherwise; when a custom ordering is needed, the comparison rule can be specified through the `compare` parameter.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T, class Compare> [[nodiscard]] constexpr const T& clamp(const T& value, const T& lower, const T& upper, Compare compare);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr const T& clamp(const T& value, const T& lower, const T& upper);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of value, lower, and upper; the three parameters must be comparable under the selected comparison rule. |
| `Compare` | Type of the custom comparison object; this object determines whether the first argument is ordered before the second. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value to be confined to the specified range. |
| `lower` | Input | Lower bound of the range. |
| `upper` | Input | Upper bound of the range. |
| `compare` | Input | Custom comparison object; compare(left, right) returning true means left is ordered before right. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Type of value, lower, and upper; the three parameters must be comparable under the selected comparison rule. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value to be confined to the specified range. |
| `lower` | Input | Lower bound of the range. |
| `upper` | Input | Upper bound of the range. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const T &` | Returns a constant reference to one of value, lower, or upper; the referenced object must remain valid while the result is in use. |
| Prototype 2 | `const T &` | Returns a constant reference to one of value, lower, or upper; the referenced object must remain valid while the result is in use. |

## Constraints

- lower and upper must form a valid range under the selected comparison relation.
- compare must establish a strict weak ordering and must not modify the objects being compared.
- The returned reference does not extend the lifetime of value, lower, or upper.

## Example

The following example handles inputs below the lower bound, within the range, and above the upper bound, and checks the return values and the objects they reference.

```cpp
#include <asc/std/algorithm>

bool example()
{
    const int lower = 0;
    const int upper = 10;
    const int below = -3;
    const int middle = 4;
    const int above = 12;

    const int& lower_result = asc::std::clamp(below, lower, upper);
    const int& middle_result = asc::std::clamp(middle, lower, upper);
    const int& upper_result = asc::std::clamp(above, lower, upper);

    // Refers to lower when below the lower bound; refers to the original value when within the range;
    // refers to upper when above the upper bound.
    return lower_result == 0 && &lower_result == &lower
        && middle_result == 4 && &middle_result == &middle
        && upper_result == 10 && &upper_result == &upper;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
