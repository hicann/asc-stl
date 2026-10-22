# asc::std::ranges::drop_view::begin

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

`asc::std::ranges::drop_view::begin` returns an iterator to the first element.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`drop_view`](ranges_drop_view.md). The following is a declaration summary listed by participation conditions; template defaults used for calls are kept, and implementation-selection parameters used only for SFINAE are omitted. When a private return type is involved, it is summarized as auto; this does not promise the type can be named directly.

### Prototype 1

```cpp
template<class View2 = View>
constexpr auto begin();
```

This non-const form is provided when the underlying view is not simultaneously a simple view, const random-access, and sized; the condition of the const form is listed separately. A "simple view" means the underlying view is a view, is iterable both as const and non-const, and the corresponding iterator and sentinel types are the same respectively.

### Prototype 2

```cpp
template<class View2 = View>
constexpr auto begin() const;
```

Participation condition: `(random_access_range<const View2> && sized_range<const View2>)`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | The owning type or kind used to defer member checks, with the default value shown in the prototype; ordinary calls do not need to specify it explicitly. |

No function parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `View2` | The owning type or kind used to defer member checks, with the default value shown in the prototype; ordinary calls do not need to specify it explicitly. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the starting iterator; the private iterator type is expressed as auto, with its dereference and movement behavior defined by the owning view. |
| Prototype 2 | `auto` | Returns the starting iterator; the private iterator type is expressed as auto, with its dereference and movement behavior defined by the owning view. |

## Constraints

- The participation condition of each form is shown in the prototype; no-argument queries are generally called directly without specifying a template selection type.
- Returned iterators, pointers, or references, as well as borrowed ranges, must not outlive the validity of the view objects and element storage they actually depend on.

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
    asc::std::ranges::drop_view<Base> view(base, 2);
    return *view.begin() == 3;
}
```

## Related APIs

- [`asc::std::ranges::drop_view`](ranges_drop_view.md)
- [API list for this header](asc_std_ranges.md)
