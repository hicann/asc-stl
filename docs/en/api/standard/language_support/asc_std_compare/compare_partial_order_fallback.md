# asc::std::compare_partial_order_fallback

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

Header: `<asc/std/compare>`.

`asc::std::compare_partial_order_fallback` is a comparison function object type. Its call operator prefers an available three-way comparison, and otherwise synthesizes an `asc::std::partial_ordering` from `==` and `<`.

Standard semantics reference: [cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare).

## Declaration

The current version exposes this interface as a class type. Construct a function object before passing the two values.

```cpp
namespace asc::std {
struct compare_partial_order_fallback {
    template <class T, class U>
    [[nodiscard]] constexpr partial_ordering operator()(T&& left, U&& right) const;
};
} // namespace asc::std
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The first value participating in the comparison. |
| `right` | Input | The second value participating in the comparison. |

## Return Value

Returns an `asc::std::partial_ordering` comparison category value; a partial ordering comparison may return unordered.

| Call form | Return type |
| --- | --- |
| Two values | `asc::std::partial_ordering` |

## Constraints

- The arguments must support an applicable three-way comparison, or support both equality and less-than comparison.

## Example

The following snippet constructs a function object and then compares two integers.

```cpp
#include <asc/std/compare>

inline constexpr auto example = asc::std::compare_partial_order_fallback{}(1, 2);
static_assert(example < 0);
```

## Related APIs

- [API list for this header](asc_std_compare.md)
