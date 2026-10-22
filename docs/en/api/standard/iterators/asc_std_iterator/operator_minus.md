# `asc::std::operator-` (move_iterator/common_iterator/counted_iterator overload) (Function template)

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

This page lists the associated non-member difference operations of the move, common, counted, and reverse iterators. They return the signed distance between two positions without moving iterators or reading elements; the direction and exception specifications are distinguished by the forms below.

## Function Prototype

The following is a declaration summary of the currently public difference operations; implementation parameters used only for SFINAE selection are omitted, and the conditions of each are given in the prototype descriptions. Prototypes 1-7 are defined in the namespace; Prototype 8 is a hidden friend of the reverse iterator. All can be used at the corresponding positions in C++17 and C++20.

### Prototype 1

```cpp
namespace asc::std {
template<class Iter, class Sentinel>
constexpr iter_difference_t<Iter> operator-(const move_sentinel<Sentinel>& sentinel,
    const move_iterator<Iter>& iterator);
}
```

sized_sentinel_for<Sentinel, Iter> must hold. C++17 and the device side use SFINAE, and Host C++20 uses requires; this condition guarantees that the underlying difference result of the C++17 declaration is the same as iter_difference_t<Iter>.

### Prototype 2

```cpp
namespace asc::std {
template<class Iter, class Sentinel>
constexpr iter_difference_t<Iter> operator-(const move_iterator<Iter>& iterator,
    const move_sentinel<Sentinel>& sentinel);
}
```

The same sized_sentinel_for condition as Prototype 1.

### Prototype 3

```cpp
namespace asc::std {
template<class I1, class S1, class I2, class S2>
constexpr iter_difference_t<I2> operator-(const common_iterator<I1, S1>& left,
    const common_iterator<I2, S2>& right);
}
```

Requires sized_sentinel_for<I2,I1>, sized_sentinel_for<S2,I1>, and sized_sentinel_for<S1,I2> to hold simultaneously; C++17 and the device side use SFINAE, and Host C++20 uses requires.

### Prototype 4

```cpp
namespace asc::std {
template<class I1, class I2>
[[nodiscard]] constexpr iter_difference_t<I2> operator-(const counted_iterator<I1>& left,
    const counted_iterator<I2>& right);
}
```

Both must represent comparable positions in the same underlying sequence, and the difference of the remaining counts must be representable.

### Prototype 5

```cpp
namespace asc::std {
template<class Iter>
constexpr iter_difference_t<Iter> operator-(default_sentinel_t sentinel,
    const counted_iterator<Iter>& value) noexcept;
}
```

The remaining count of value must be valid and representable by the returned difference type.

### Prototype 6

```cpp
namespace asc::std {
template<class Iter>
constexpr iter_difference_t<Iter> operator-(const counted_iterator<Iter>& value,
    default_sentinel_t sentinel) noexcept;
}
```

The remaining count of value and its negation must be representable by the returned difference type.

### Prototype 7

```cpp
namespace asc::std {
template<class Left, class Right>
constexpr auto operator-(const move_iterator<Left>& left, const move_iterator<Right>& right)
    -> decltype(left.base() - right.base());
}
```

The underlying left.base()-right.base() expression must be valid, and the two underlying positions must belong to the same sequence whose difference can be taken.

### Prototype 8

```cpp
template<class Iter2>
friend constexpr auto operator-(const reverse_iterator& left, const reverse_iterator<Iter2>& right)
    -> decltype(::asc::std::declval<const Iter2&>() - ::asc::std::declval<const Iter&>());
```

This prototype is inside the reverse_iterator<Iter> class; it is a hidden friend and must be used with the left-right operator syntax. The underlying difference expression in reverse order must be valid.

## Parameters

The template parameters Iter/Left/Right/I1/I2 are underlying iterator types, and Sentinel/S1/S2 are the sentinel types paired with the corresponding iterators. The selection conditions of each are given in the prototype descriptions.

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `sentinel` | Input | The move sentinel on the left of the minus sign. |
| `iterator` | Input | The move iterator on the right of the minus sign. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The move iterator on the left of the minus sign. |
| `sentinel` | Input | The move sentinel on the right of the minus sign. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left common_iterator holding an iterator or sentinel state. |
| `right` | Input | The right common_iterator holding an iterator or sentinel state. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left counted iterator. |
| `right` | Input | The right counted iterator. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `sentinel` | Input | The end marker indicating that the remaining count is 0. |
| `value` | Input | The counted iterator that counts from the current position to the end. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The left counted iterator. |
| `sentinel` | Input | The right end marker. |

### Parameters of Prototype 7

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left move iterator. |
| `right` | Input | The right move iterator. |

### Parameters of Prototype 8

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left reverse iterator. |
| `right` | Input | The right reverse iterator. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `iter_difference_t<Iter>` | sentinel.base() - iterator.base(). |
| Prototype 2 | `iter_difference_t<Iter>` | iterator.base() - sentinel.base(). |
| Prototype 3 | `iter_difference_t<I2>` | Returns 0 when both sides are sentinels; in the other states it subtracts right from left according to each side's currently stored position. |
| Prototype 4 | `iter_difference_t<I2>` | right.count() - left.count(), that is, the signed distance of advancing from the right position to the left position. |
| Prototype 5 | `iter_difference_t<Iter>` | value.count(): the end position minus the current position. |
| Prototype 6 | `iter_difference_t<Iter>` | -value.count(): the current position minus the end position. |
| Prototype 7 | `decltype(left.base() - right.base())` | The left underlying position minus the right underlying position. |
| Prototype 8 | `decltype(right.base() - left.base())` | right.base() - left.base(), the reverse of the subtraction order of the underlying forward positions. |

## Constraints

- The two positions must belong to the same underlying sequence and satisfy the difference or sized_sentinel_for condition listed by that prototype; the difference must be representable.
- Counted iterators compute the position difference from the remaining count and do not require access to elements; the default sentinel is located at the position where the remaining count is 0.
- The difference order of reverse iterators is the reverse of the base iterator's; the hidden friend is found through operator expression lookup.
- Only Prototypes 5 and 6 explicitly declare noexcept; the other forms must not all be treated as non-throwing.
- None of the adaptors take ownership of the underlying storage; the storage and positions must remain valid during the operation.

## Example

The following Host example checks the direction and results of the operations within the lifetime of the same underlying array.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[4] = {2, 4, 6, 8};
    const asc::std::move_iterator<int*> moved_first(values), moved_later(values + 2);
    const asc::std::move_sentinel<int*> moved_end(values + 4);
    const asc::std::counted_iterator<int*> counted_first(values, 4), counted_later(values + 2, 2);
    using common_type = asc::std::common_iterator<int*, const int*>;
    const common_type common_first(values), common_end(static_cast<const int*>(values + 4));
    const asc::std::reverse_iterator<int*> reversed_first(values + 4), reversed_later(values + 2);
    return moved_end - moved_first == 4 && moved_first - moved_end == -4
        && moved_later - moved_first == 2 && counted_later - counted_first == 2
        && asc::std::default_sentinel - counted_first == 4
        && counted_first - asc::std::default_sentinel == -4
        && common_end - common_first == 4 && common_end - common_end == 0
        && reversed_later - reversed_first == 2;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
