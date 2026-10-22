# asc::std::ranges::filter_view::filter_view

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

`asc::std::ranges::filter_view::filter_view` initializes a `filter_view` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`filter_view`](ranges_filter_view.md). The following lists declaration summaries by the current implementation; selection parameters used only for SFINAE are omitted, and type defaults used for calls are kept. Default construction forms each have per-form participation conditions; do not assume all specializations are default constructible based on this.

### Prototype 1

```cpp
template<class View2 = View, class Pred2 = Pred>
constexpr filter_view() noexcept(is_nothrow_default_constructible_v<View2>
    && is_nothrow_default_constructible_v<Pred2>);
```

Both View2 and Pred2 must satisfy default_initializable; the defaults are View and Pred of the owning view respectively.

### Prototype 2

```cpp
constexpr explicit filter_view(View base, Pred predicate) noexcept(
    is_nothrow_move_constructible_v<View> && is_nothrow_move_constructible_v<Pred>);
```

Explicitly stores the moved range and predicate. The exception specification uses public type traits to express the same condition as construction of the internal predicate box.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | The deferred-check type of the underlying view, defaulting to View. |
| `Pred2` | The deferred-check type of the predicate, defaulting to Pred. |

No function parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | The underlying view to be filtered. |
| `predicate` | Input | The predicate that decides whether underlying elements are kept; received by value and stored by move. |

## Return Value

No return value.

## Constraints

- Each form must satisfy the participation conditions listed in its prototype; the actually stored range or value must also satisfy the type requirements of the owning view.
- Constructing the view does not copy the elements it borrows; the underlying storage and borrowed objects must cover the corresponding iterator and element access periods.
- Forms marked noexcept must satisfy the requirement that the actual member operations do not throw; see each prototype for the specific exception specification.

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
    auto predicate = [](int value) { return value % 2 == 0; };
    asc::std::ranges::filter_view<Base, decltype(predicate)> view(base, predicate);
    return *view.begin() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
