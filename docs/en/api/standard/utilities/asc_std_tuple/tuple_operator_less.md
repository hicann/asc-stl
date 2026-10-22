# `asc::std::operator<` (tuple)

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

`asc::std::operator<` (tuple free comparison function template) compares the order of two objects.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
template<class... Left, class... Right> constexpr bool asc::std::operator<(const tuple<Left...>& left, const tuple<Right...>& right);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Left`, `Right` | The element type packs of the two tuples; the number of elements must be the same. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left`, `right` | Input | The two tuples being compared. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the two tuples compare less in lexicographic order, and `false` otherwise. |

## Constraints

- The two tuples must have the same number of elements; each pair of corresponding elements must support the comparison required by this operation.
- Equality requires all corresponding elements to be equal; ordered comparisons are lexicographic, and the result is determined by the first unequal element.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and parameters must satisfy the constraints on this page.

```cpp
#include <asc/std/tuple>

decltype(auto) example()
{
    asc::std::tuple<int, int> left(1, 2), right(3, 4);
    return (left < right);
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
