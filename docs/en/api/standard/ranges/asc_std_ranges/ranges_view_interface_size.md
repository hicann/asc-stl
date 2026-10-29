# asc::std::ranges::view_interface::size

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

`asc::std::ranges::view_interface::size` returns the number of elements contained in the current object.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`view_interface`](ranges_view_interface.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
template<class Derived2 = Derived>
constexpr auto size();
```

`Derived2` must have forward iterators, and its sentinel and iterator must satisfy `sized_sentinel_for`.

### Prototype 2

```cpp
template<class Derived2 = Derived>
constexpr auto size() const;
```

`const Derived2` must have forward iterators, and its sentinel and iterator must satisfy `sized_sentinel_for`.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Derived2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Derived2` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

No function parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns the number of elements in the current range; the exact integer type of auto is determined by the corresponding size computation and can be queried with decltype(object.size()). |
| Prototype 2 | `auto` | Returns the number of elements in the current range; the exact integer type of auto is determined by the corresponding size computation and can be queried with decltype(object.size()). |

## Constraints

- For the participation constraints of each form, see the prototypes; a query with no arguments is generally called directly and does not require specifying a template selection type.

## Example

The following Host snippet demonstrates the call with a concrete range or accessor; the underlying storage must remain valid during the call.

```cpp
#include <asc/std/ranges>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::ref_view<int[4]> view(values);
    return view.size();
}

bool verify_example()
{
    return example() == 4;
}
```

## Related APIs

- [`asc::std::ranges::view_interface`](ranges_view_interface.md)
- [API list for this header](asc_std_ranges.md)
