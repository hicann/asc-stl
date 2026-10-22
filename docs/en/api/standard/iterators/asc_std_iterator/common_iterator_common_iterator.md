# asc::std::common_iterator::common_iterator

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

`asc::std::common_iterator::common_iterator` initializes a `common_iterator` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::common_iterator`](common_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside common_iterator.
template<class I2 = Iter, enable_if_t<default_initializable<I2>, int> = 0>
constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside common_iterator.
constexpr common_iterator(Iter value) noexcept(is_nothrow_move_constructible_v<Iter>);
```

### Prototype 3

```cpp
// Excerpt of the declaration inside common_iterator.
constexpr common_iterator(Sent value) noexcept(is_nothrow_move_constructible_v<Sent>);
```

### Prototype 4

```cpp
// Excerpt of the declaration inside common_iterator.
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(common_iterator&&) = default;
```

### Prototype 5

```cpp
// Excerpt of the declaration inside common_iterator.
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(const common_iterator&) = default;
```

### Prototype 6

```cpp
// Excerpt of the declaration inside common_iterator.
template<class I2, class S2, enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent>, int> = 0>
constexpr common_iterator(const common_iterator<I2, S2>& other) noexcept(
    is_nothrow_constructible_v<Iter, const I2&> && is_nothrow_constructible_v<Sent, const S2&>);
```

The default constructor and converting constructor show the selection form used by C++17 and Device; Host C++20 uses an equivalent `requires` condition. `CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20` is `constexpr` in C++20 and above and empty in C++17.

## Parameters

| Parameter | Description |
| --- | --- |
| `I2` | Defaults to `Iter` for the default constructor; for the converting constructor it is the source iterator type. |
| `S2` | The source sentinel type for conversion; it must be convertible-constructible to `Sent`. |

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | An iterator or sentinel. After construction only the corresponding one of the two states is stored; the underlying range must remain valid. |
| `other` | Input | The source common iterator for conversion, constructed according to its currently stored state. |

The source parameters of the copy and move constructors are unnamed in the declaration; they copy or move the stored state, respectively.

## Return Value

No return value.

## Constraints

- `Iter` and `Sent` are distinct types and must satisfy the pairing requirements of input/output iterators and sentinels; the adaptor stores one of the two states.
- Dereference, arrow access, and increment can only act on an object that currently holds an iterator for which the operation is valid, not on the sentinel state.
- The adaptor does not own the underlying range; the pointed-to objects must remain valid during access.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/utility>

bool example()
{
    int values[] = {2, 4};
    using It = asc::std::counted_iterator<int*>;
    using ConstIt = asc::std::counted_iterator<const int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common empty;
    Common direct(It(values, 2));
    Common last(asc::std::default_sentinel);
    Common copied(direct);
    Common moved(asc::std::move(copied));
    asc::std::common_iterator<ConstIt, asc::std::default_sentinel_t> converted(direct);
    return empty == last && *moved == 2 && *converted == 2;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
