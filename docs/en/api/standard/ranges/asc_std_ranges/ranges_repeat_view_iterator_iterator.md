# asc::std::ranges::repeat_view::iterator::iterator

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

Header: `<asc/std/ranges>`.

The default construction of `repeat_view::iterator`, producing an iterator associated with the default value.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

This page describes the iterator returned by repeat_view. The type name must be obtained through decltype(view.begin()); iterator is only the owning type name used in the class declaration summary below.

### Prototype 1

```cpp
constexpr iterator() = default;
```

### Prototype 2

```cpp
constexpr explicit iterator(const T* value,
    conditional_t<is_same_v<Bound, unreachable_sentinel_t>, ptrdiff_t, Bound> position = {})
    noexcept(is_nothrow_copy_constructible_v<
        conditional_t<is_same_v<Bound, unreachable_sentinel_t>, ptrdiff_t, Bound>>);
```

## Parameters

Prototype 1 has no parameters. In Prototype 2, value points to the live T object being repeated, and position is the current position stored in the iterator, defaulting to 0; the unbounded specialization uses ptrdiff_t, and the bounded specialization uses Bound.

## Return Value

The constructors have no return value; dereferencing the iterator returns a const T& to the stored object.

## Constraints

- A default-constructed iterator is not associated with an object and must not be dereferenced.
- The object stored in a valid iterator must cover its access period, and position arithmetic must not exceed the representable range; ordinary iterators are obtained through view.begin().

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>

bool example()
{
    auto view = asc::std::ranges::views::repeat(7, 3);
    using iterator_type = decltype(view.begin());
    const iterator_type first(view.begin());
    const iterator_type copied(first);
    return copied == first && *copied == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
