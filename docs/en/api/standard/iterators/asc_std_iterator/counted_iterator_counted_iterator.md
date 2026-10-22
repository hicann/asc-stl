# asc::std::counted_iterator::counted_iterator

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

`asc::std::counted_iterator::counted_iterator` initializes a `counted_iterator` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::counted_iterator`](counted_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside counted_iterator.
template<class I2 = Iter, enable_if_t<is_default_constructible_v<I2>, int> = 0>
constexpr counted_iterator();
```

### Prototype 2

```cpp
// Excerpt of the declaration inside counted_iterator.
constexpr counted_iterator(Iter value, difference_type count) noexcept(is_nothrow_move_constructible_v<Iter>);
```

### Prototype 3

```cpp
// Excerpt of the declaration inside counted_iterator.
template<class I2, enable_if_t<is_convertible_v<const I2&, Iter>, int> = 0>
constexpr counted_iterator(const counted_iterator<I2>& other) noexcept(is_nothrow_constructible_v<Iter, const I2&>);
```

The above are the C++17 and Device selection forms; Host C++20 expresses the corresponding conditions with `requires`, and the default constructor is defaulted.

## Parameters

| Parameter | Description |
| --- | --- |
| `I2` | The selection parameter for the default constructor defaults to `Iter`; for the converting constructor it is the source underlying iterator type. |

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The current underlying iterator; from this position there must be `count` valid elements. |
| `count` | Input | The number of remaining elements, which must be non-negative; 0 means an empty counted range. |
| `other` | Input | The source counted iterator for conversion, copying both its current position and remaining count. |

## Return Value

No return value.

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
    int values[] = {2, 4};
    asc::std::counted_iterator<int*> empty;
    asc::std::counted_iterator<int*> direct(values, 2);
    asc::std::counted_iterator<const int*> converted(direct);
    return empty.count() == 0 && converted.count() == 2 &&
           converted.base() == values && *converted == 2;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
