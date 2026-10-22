# asc::std::common_iterator::`operator=`

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

`asc::std::common_iterator::operator=` updates the object through the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::common_iterator`](common_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside common_iterator.
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(common_iterator&&) = default;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside common_iterator.
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(const common_iterator&) = default;
```

### Prototype 3

```cpp
// Excerpt of the declaration inside common_iterator.
template<class I2, class S2,
    enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent> &&
        assignable_from<Iter&, const I2&> && assignable_from<Sent&, const S2&>, int> = 0>
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(const common_iterator<I2, S2>& other);
```

The converting assignment shows the C++17 and Device form; Host C++20 expresses the same condition with `requires` and declares it `constexpr`. The macro `CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20` is `constexpr` in C++20 and above and empty in C++17.

## Parameters

| Parameter | Description |
| --- | --- |
| `I2` | The source iterator type for conversion; it must be convertible-constructible and assignable to `Iter`. |
| `S2` | The source sentinel type for conversion; it must be convertible-constructible and assignable to `Sent`. |

In the converting assignment, `other` is the input source object. The source parameters of the first two special assignment members are unnamed in the declaration; they perform move or copy assignment, respectively.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `common_iterator<Iter, Sent> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |
| Prototype 2 | `common_iterator<Iter, Sent> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |
| Prototype 3 | `common_iterator<Iter, Sent> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |

## Constraints

- `Iter` and `Sent` are distinct types and must satisfy the pairing requirements of input/output iterators and sentinels; the adaptor stores one of the two states.
- Dereference, arrow access, and increment can only act on an object that currently holds an iterator for which the operation is valid, not on the sentinel state.
- The adaptor does not own the underlying range; the pointed-to objects must remain valid during access.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using It = asc::std::counted_iterator<int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common iterator(It(values, 3));
    Common target(asc::std::default_sentinel);
    target = iterator;
    return *target == 2;
}
```

## Related APIs

- [`asc::std::common_iterator`](common_iterator.md)
- [API list for this header](asc_std_iterator.md)
