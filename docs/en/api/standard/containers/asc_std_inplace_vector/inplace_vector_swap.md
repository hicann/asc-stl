# asc::std::inplace_vector::swap

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

Header: `<asc/std/inplace_vector>`.

`asc::std::inplace_vector::swap` exchanges the state or elements held by two objects.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr void swap(inplace_vector& other);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | Another container with the same capacity; after the swap both hold the other's original sequence. |

## Return Value

No return value.

## Constraints

- The two objects have the same capacity; common elements are swapped, and the elements corresponding to the size difference on each side are move-constructed or destroyed.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host snippet demonstrates the call with a concrete capacity or dimension; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/inplace_vector>

void example(asc::std::inplace_vector<int, 8>& left, asc::std::inplace_vector<int, 8>& right)
{
    left.swap(right);
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
