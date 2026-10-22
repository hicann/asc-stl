# asc::std::inplace_vector::erase

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

`asc::std::inplace_vector::erase` erases elements by iterator position or half-open range, compacts the following elements, and returns the new iterator following the erased position.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr iterator erase(const_iterator position);
```

### Prototype 2

```cpp
constexpr iterator erase(const_iterator first, const_iterator last);
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `position` | Input | A dereferenceable erase position in this container; it must not be end(). |

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start of the half-open range to erase; together with last it forms a valid ordered sub-range of this container. |
| `last` | Input | The past-the-end position of the range to erase; it may be end(), and first==last means nothing is erased. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `iterator` | Returns the element position following the erased position; it is the new end() when erasing through the end. |
| Prototype 2 | `iterator` | Returns the new position corresponding to the original first; it is the new end() when erasing through the end, and an empty range leaves the container unchanged. |

## Constraints

- position must be a dereferenceable position in this container; the range form requires [first,last) to be a valid ordered sub-range of this container.
- Compacts the following elements by move assignment and destroys the tail; old positions may come to denote other elements, so use the returned new iterator.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/inplace_vector>

bool example()
{
    asc::std::inplace_vector<int, 4> values;
    if (!values.try_push_back(2) || !values.try_push_back(3)) return false;
    const auto next = values.erase(values.begin());
    return values.size() == 1 && next == values.begin() && *next == 3;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
