# asc::std::ranges::ref_view::ref_view

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

`asc::std::ranges::ref_view::ref_view` initializes a `ref_view` object with the construction forms listed on this page.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`ref_view`](ranges_ref_view.md). The following lists declaration summaries by the current implementation; selection parameters used only for SFINAE are omitted, and type defaults used for calls are kept. Default construction forms each have per-form participation conditions; do not assume all specializations are default constructible based on this.

### Prototype 1

```cpp
template<class T>
constexpr ref_view(T&& object);
```

After removing cv/ref from T it must not be a specialization of this ref_view; the input must be implicitly convertible to and actually bind to an Range& lvalue, and binding a temporary Range as the borrowing source is not allowed. This constructor currently has no explicit qualifier.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the source object or value; see the prototype participation condition for requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input | The borrowed range lvalue, or an object convertible to that range lvalue; the function stores its address. |

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
    asc::std::ranges::ref_view<int[4]> view(values);
    return *view.begin() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
