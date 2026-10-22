# asc::std::ranges::subrange::size

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

`asc::std::ranges::subrange::size` returns the number of elements contained in the current object.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`subrange`](ranges_subrange.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
template<subrange_kind Kind_ = Kind>
constexpr make_unsigned_t<iter_difference_t<Iter>> size() const;
```

Participation constraint: `((Kind_ == subrange_kind::sized))`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Kind_` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `make_unsigned_t<iter_difference_t<Iter>>` | Returns the number of elements in the current range; the exact integer type of auto is determined by the corresponding size computation and can be queried with decltype(object.size()). |

## Constraints

- For the participation constraints of each form, see the prototypes; a query with no arguments is generally called directly and does not require specifying a template selection type.

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
    Base view(values, values + 4);
    return view.size() == 4;
}
```

## Related APIs

- [`asc::std::ranges::subrange`](ranges_subrange.md)
- [API list for this header](asc_std_ranges.md)
