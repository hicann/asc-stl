# asc::std::ranges::reverse_view::begin

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

`asc::std::ranges::reverse_view::begin` returns an iterator to the first element.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`reverse_view`](ranges_reverse_view.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly. The two non-const templates have mutually exclusive common_range conditions.

### Prototype 1

```cpp
template<class View2 = View>
constexpr reverse_iterator<iterator_t<View2>> begin();
```

Participation constraint: `((!common_range<View2>))`.

### Prototype 2

```cpp
template<class View2 = View>
constexpr reverse_iterator<iterator_t<View2>> begin();
```

Participation constraint: `(common_range<View2>)`.

### Prototype 3

```cpp
template<class View2 = View>
constexpr auto begin() const;
```

Participation constraint: `(common_range<const View2>)`.

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

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `reverse_iterator<iterator_t<View2>>` | Returns the starting iterator; the private iterator type is represented as auto, and its dereference and movement behavior is defined by the owning view. |
| Prototype 2 | `reverse_iterator<iterator_t<View2>>` | Returns the starting iterator; the private iterator type is represented as auto, and its dereference and movement behavior is defined by the owning view. |
| Prototype 3 | `auto` | Returns the starting iterator; the private iterator type is represented as auto, and its dereference and movement behavior is defined by the owning view. |

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
    asc::std::ranges::reverse_view<Base> view(base);
    return *view.begin() == 4;
}
```

## Related APIs

- [`asc::std::ranges::reverse_view`](ranges_reverse_view.md)
- [API list for this header](asc_std_ranges.md)
