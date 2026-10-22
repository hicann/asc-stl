# asc::std::ranges::zip_view::begin

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

`asc::std::ranges::zip_view::begin` returns an iterator to the first element.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`zip_view`](ranges_zip_view.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
constexpr auto begin();
```

This form has no additional member template participation constraints; the requirements of the owning type must still be satisfied.

### Prototype 2

```cpp
constexpr auto begin() const;
```

This form has no additional member template participation constraints; the requirements of the owning type must still be satisfied.

## Parameters

### Parameters of Prototype 1

No function parameters.

### Parameters of Prototype 2

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the starting iterator; the private iterator type is represented as auto, and its dereference and movement behavior is defined by the owning view. |
| Prototype 2 | `auto` | Returns the starting iterator; the private iterator type is represented as auto, and its dereference and movement behavior is defined by the owning view. |

## Constraints

- For the participation constraints of each form, see the prototypes; a query with no arguments is generally called directly and does not require specifying a template selection type.
- The returned iterators, pointers, or references, as well as borrowed ranges, must not outlive the view objects and element storage they actually depend on.
- The current zip stores exactly two ranges; its iterators must support random access, and the ranges must be sized. The const form additionally requires the const iterator types of both sides to be identical to their non-const forms; these conditions are checked at instantiation.

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
    asc::std::ranges::zip_view<Base, Base> view(base, base);
    return asc::std::get<0>(*view.begin()) == 1;
}
```

## Related APIs

- [`asc::std::ranges::zip_view`](ranges_zip_view.md)
- [API list for this header](asc_std_ranges.md)
