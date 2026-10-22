# asc::std::counted_iterator::`operator=`

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

Header: `<asc/std/iterator>`.

`asc::std::counted_iterator::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`counted_iterator`](counted_iterator.md). The following preserves the real participation conditions of the converting assignment; C++17 and Device select with SFINAE, and Host C++20 selects with the same requires condition.

```cpp
template<class I2, enable_if_t<assignable_from<Iter&, const I2&>, int> = 0>
constexpr counted_iterator& operator=(const counted_iterator<I2>& other) noexcept(is_nothrow_assignable_v<Iter&, const I2&>);
```

Same-type special member assignments follow the C++ implicit declaration rules.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `I2` | The iterator type used to traverse the input range; it must satisfy the traversal capabilities required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The source of the converting assignment, taken as a const reference; the stored underlying state must satisfy the conversion and assignment conditions given by the prototype. |

## Return Value

| Return type | Description |
| --- | --- |
| `counted_iterator&` | Copies the current underlying position and remaining count from the source and returns *this; the source remains valid. |

## Constraints

- `Iter` must satisfy the traversal capabilities required by this operation; the adaptor does not own the underlying range.
- `count()` gives the number of elements remaining from the current position; dereference and increment require the remaining count to be greater than 0.
- The underlying position after the shift and the corresponding count must be valid and must not go beyond the actually valid range.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::counted_iterator<int*> iterator(values, 4);
    asc::std::counted_iterator<const int*> target;
    target = iterator;
    return *target == 2;
}
```

## Related APIs

- [`asc::std::counted_iterator`](counted_iterator.md)
- [API list for this header](asc_std_iterator.md)
