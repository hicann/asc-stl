# asc::std::ranges::transform_view::base

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

`asc::std::ranges::transform_view::base` returns the underlying iterator or object stored by the adaptor.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`transform_view`](ranges_transform_view.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
template<class View2 = View>
constexpr View base() const&;
```

Participation constraint: `(copy_constructible<View2>)`.

### Prototype 2

```cpp
constexpr View base() &&;
```

This form has no additional member template participation constraints; the requirements of the owning type must still be satisfied.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

### Parameters of Prototype 2

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `View` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding references as declared. When returning references or borrowed ranges, the lifetime of the original storage must be respected. |
| Prototype 2 | `View` | Returns the stored underlying range; the const lvalue form copies, the rvalue form moves, and the forms of owning_view return the corresponding references as declared. When returning references or borrowed ranges, the lifetime of the original storage must be respected. |

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
    auto operation = [](int value) { return value * 3; };
    asc::std::ranges::transform_view<Base, decltype(operation)> view(base, operation);
    return *asc::std::ranges::begin(view.base()) == 1;
}
```

## Related APIs

- [`asc::std::ranges::transform_view`](ranges_transform_view.md)
- [API list for this header](asc_std_ranges.md)
