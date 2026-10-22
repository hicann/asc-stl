# `asc::std::operator<` (pair)

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

Header: `<asc/std/utility>`.

Compares the two members of a pair. Equality comparison requires each of the two members to be equal; the less-than comparison checks first first, and checks second only when first is equivalent.

## Function Prototype

The following are function template declarations in the `asc::std` namespace; execution-space macros are omitted.

```cpp
template<class T1, class T2>
constexpr bool operator<(const pair<T1, T2>& left, const pair<T1, T2>& right)
    noexcept(noexcept(left.first < right.first && left.second < right.second));
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left operand of the comparison; the comparison does not modify it. |
| `right` | Input | The right operand of the comparison; the comparison does not modify it. |

`T1` and `T2` are the first and second element types of the pair.

## Return Value

Returns `bool`: `true` when the comparison relation holds, `false` otherwise.

## Constraints

- The elements must support the corresponding comparison. The exception specification is determined by the expression in the declaration.
- The direct free overloads for pair in the current `asc::std` are `==` and `<`; the generic relational helpers in `rel_ops` are not listed here.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/utility>

bool example()
{
    asc::std::pair<int, int> left{1, 2};
    asc::std::pair<int, int> right{1, 3};
    return left < right;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
