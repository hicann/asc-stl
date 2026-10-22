# asc::std::ranges::common_view::common_view

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

`asc::std::ranges::common_view::common_view` initializes a `common_view` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`common_view`](ranges_common_view.md). The following lists declaration summaries by the current implementation; selection parameters used only for SFINAE are omitted, and type defaults used for calls are kept. Default construction forms each have per-form participation conditions; do not assume all specializations are default constructible based on this.

### Prototype 1

```cpp
constexpr common_view();
```

Participates only when View satisfies default_initializable; different language paths use defaulted construction or SFINAE selection respectively.

### Prototype 2

```cpp
constexpr explicit common_view(View base)
    noexcept(is_nothrow_move_constructible_v<View>);
```

Explicitly moves to store the underlying view; elements are not copied.

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `base` | Input | The view used to initialize the underlying range. |

## Return Value

No return value.

## Constraints

- Each form must satisfy the participation conditions listed in its prototype; the actually stored range or value must also satisfy the type requirements of the owning view.
- Constructing the view does not copy the elements it borrows; the underlying storage and borrowed objects must cover the corresponding iterator and element access periods.
- Forms marked noexcept must satisfy the requirement that the actual member operations do not throw; see each prototype for the specific exception specification.

## Example

This example uses iterators and sentinels of different types; common_view converts them into first and last positions representable by the same type.

```cpp
#include <asc/std/ranges>
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using Iterator = asc::std::counted_iterator<int*>;
    using Base = asc::std::ranges::subrange<Iterator, asc::std::default_sentinel_t>;
    Base base(Iterator(values, 3), asc::std::default_sentinel);
    asc::std::ranges::common_view<Base> view(base);
    return *view.begin() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
