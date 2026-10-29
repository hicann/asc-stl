# asc::std::inplace_vector::erase_if

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

`asc::std::inplace_vector::erase_if` removes elements from the fixed-capacity container by predicate and returns the number of erased elements.

This interface supports both Host and the device side, both limited to the non-throwing operations listed on this page.

Standard semantics reference: [cppreference `inplace_vector`](https://en.cppreference.com/w/cpp/header/inplace_vector).

## Function Prototype

Member of: [`inplace_vector<T, Capacity>`](inplace_vector.md). The following is the in-class declaration; type aliases and template parameters are provided by the owning class.

### Prototype 1

```cpp
template<class Predicate>
constexpr size_type erase_if(Predicate predicate);
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Predicate` | A predicate type that can be called with an element and whose result is usable as a boolean condition. |

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `predicate` | Input | The predicate, stored by value; it returns true for elements to be removed and must not change the container structure during traversal. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `size_type` | Returns the actual number of removed elements; 0 when no element matches. |

## Constraints

- predicate is applied to elements one by one; elements for which it returns true are removed, and the remaining elements keep their relative order.
- The predicate must not change the container structure during traversal; element move assignment and destruction must be valid.
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
    values.unchecked_push_back(-1);
    values.unchecked_push_back(7);
    values.unchecked_push_back(-3);
    const auto erased = values.erase_if([](int item) { return item < 0; });
    return erased == 2 && values.size() == 1 && values[0] == 7;
}
```

## Related APIs

- [`asc::std::inplace_vector`](inplace_vector.md)
- [API list for this header](asc_std_inplace_vector.md)
