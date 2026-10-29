# asc::std::inplace_vector::`operator=`

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

`asc::std::inplace_vector::operator=` updates the object according to the selected assignment overload and returns the specified result.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
constexpr inplace_vector& operator=(const inplace_vector& other);
```

### Prototype 2

```cpp
constexpr inplace_vector& operator=(inplace_vector&& other);
```

## Parameters

### Parameters of Prototype 1

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The copy assignment source; assignment proceeds over the common prefix, and the size difference is constructed or destroyed. |

### Parameters of Prototype 2

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The move assignment source; the source size is unchanged, and the elements may be moved. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `inplace_vector&` | Returns a reference to *this; the receiving object must cover the period of use of this reference. |
| Prototype 2 | `inplace_vector&` | Returns a reference to *this; the receiving object must cover the period of use of this reference. |

## Constraints

- The corresponding element copy/move construction and assignment must be valid; after the move the source keeps its element count, and the element state is determined by T.
- The corresponding construction, assignment, and destruction of elements must satisfy the non-throwing usage domain; the constexpr declaration does not guarantee constant evaluation for every T and language mode.

## Example

The following Host snippet demonstrates the call with a concrete capacity or dimension; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/inplace_vector>
#include <memory>

bool example()
{
    using sequence = asc::std::inplace_vector<int, 8>;
    sequence values;
    values.unchecked_push_back(7);
    sequence target;
    target = values;
    return !target.empty() && target.front() == 7;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
