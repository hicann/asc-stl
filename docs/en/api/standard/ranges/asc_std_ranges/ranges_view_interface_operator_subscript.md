# asc::std::ranges::view_interface::`operator[]`

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

`asc::std::ranges::view_interface::operator[]` accesses the specified element when the caller guarantees the index is valid.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`view_interface`](ranges_view_interface.md). The following lists declaration summaries by participation constraints; template defaults kept for calls are preserved, and parameters used only for SFINAE implementation selection are omitted. Where a private return type is involved, it is summarized as auto, without promising that the type can be named directly.

### Prototype 1

```cpp
template<class RARange = Derived>
constexpr decltype(auto) operator[](range_difference_t<RARange> index);
```

`RARange` must have random-access iterators.

### Prototype 2

```cpp
template<class RARange = const Derived>
constexpr decltype(auto) operator[](range_difference_t<RARange> index) const;
```

`RARange` must have random-access iterators.

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RARange` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The random-access offset from the start of the range; it must be non-negative and less than the current element count. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RARange` | Used to defer checking of the member's owning type or kind; the default value is given in the prototype. It generally does not need to be specified explicitly in a call. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The random-access offset from the start of the range; it must be non-negative and less than the current element count. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `decltype(auto)` | Returns the dereference result of the element at the specified offset, preserving the value category. |
| Prototype 2 | `decltype(auto)` | Returns the dereference result of the element at the specified offset, preserving the value category. |

## Constraints

- For the participation constraints of each form, see the prototypes; a query with no arguments is generally called directly and does not require specifying a template selection type.
- The returned iterators, pointers, or references, as well as borrowed ranges, must not outlive the view objects and element storage they actually depend on.
- index must be within the valid subscripts of the range; this interface provides no dynamic bounds protection.

## Example

The following Host snippet completes the access while the underlying storage is alive and returns a copy of the element value, without returning a reference to a local array element out of the function.

```cpp
#include <asc/std/ranges>

int read_first_element()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::ref_view<int[4]> view(values);
    // 前置条件：index < size()；operator[] 不执行边界检查
    return view[0];
}

bool verify_example()
{
    return read_first_element() == 1;
}
```

## Related APIs

- [`asc::std::ranges::view_interface`](ranges_view_interface.md)
- [API list for this header](asc_std_ranges.md)
