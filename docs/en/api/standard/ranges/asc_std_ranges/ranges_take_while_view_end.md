# asc::std::ranges::take_while_view::end

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

`asc::std::ranges::take_while_view::end` returns an iterator to the position past the end.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`take_while_view`](ranges_take_while_view.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
template<class View2 = View>
constexpr auto end();
```

This non-const form is provided when the underlying view is not a "simple view"; simple views can use the applicable const form. A "simple view" means the underlying view is a view, both const and non-const are iterable, and the corresponding iterator and sentinel types are the same, respectively.

### Prototype 2

```cpp
template<class View2 = View>
constexpr auto end() const;
```

Participation constraint: `((range<const View2> && indirect_unary_predicate<const Pred, iterator_t<const View2>>))`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the past-the-end iterator or sentinel, which is not dereferenceable; whether it has the same type as begin is determined by the owning view and the underlying range. |
| Prototype 2 | `auto` | Returns the past-the-end iterator or sentinel, which is not dereferenceable; whether it has the same type as begin is determined by the owning view and the underlying range. |

## Constraints

- For the participation constraints of each form, see the prototypes; a query with no arguments is generally called directly and does not require specifying a template selection type.
- The returned iterators, pointers, or references, as well as borrowed ranges, must not outlive the view objects and element storage they actually depend on.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    auto predicate = [](int value) { return value < 3; };
    asc::std::ranges::take_while_view<Base, decltype(predicate)> view(base, predicate);
    auto last = view.end();
    unsigned int count = 0;
    for (auto it = view.begin(); it != last; ++it) ++count;
    return count == 2;
}
```

## Related APIs

- [`asc::std::ranges::take_while_view`](ranges_take_while_view.md)
- [API list for this header](asc_std_ranges.md)
