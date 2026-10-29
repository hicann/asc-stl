# asc::in_range

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

Header: `<asc/utility>`.

`asc::in_range` determines whether `value` lies within the closed interval `[first, last]`, including both endpoints.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr bool in_range(T value, T first, T last) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Arithmetic type shared by the three operands; value, first, and last must be of the same type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Value to check; returns true when it lies within the closed interval [first, last] (both endpoints included). |
| `first` | Input | Lower endpoint of the closed interval (inclusive); must satisfy first <= last. |
| `last` | Input | Upper endpoint of the closed interval (inclusive); must satisfy first <= last. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- `value`, `first`, and `last` use the same type and must support `>=` and `<=` comparisons; when `first > last`, no value satisfies the closed-interval condition.

## Example

The following snippet provides concrete template arguments and the entity being called.

```cpp
#include <asc/utility>

decltype(auto) example()
{
    return asc::in_range(3, 0, 10);
}

bool verify_example()
{
    return example() == true;
}
```

## Related APIs

- [API list for this header](asc_utility.md)
