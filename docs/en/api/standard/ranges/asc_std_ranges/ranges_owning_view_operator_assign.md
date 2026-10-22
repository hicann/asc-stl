# asc::std::ranges::owning_view::`operator=`

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

`asc::std::ranges::owning_view::operator=` updates the object with the selected assignment overload and returns the specified result.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`asc::std::ranges::owning_view`](ranges_owning_view.md).

```cpp
// Excerpt of the declaration inside the asc::std::ranges::owning_view class; template parameters and other members are provided by the enclosing class.
owning_view<Rp>& operator=(owning_view<Rp>&& other);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The assignment source object; the lvalue form copies its state, and the rvalue form transfers state through the move operations of the corresponding members. |

## Return Value

| Return type | Description |
| --- | --- |
| `owning_view<Rp> &` | Returns a reference to the updated current object, which can continue to be assigned or used in compound operations. |

## Constraints

- Element access and iteration on the view do not allocate additional storage; the underlying range's lifetime must cover all uses of borrowed views.
- owning_view only owns the range object passed in by the caller and performs no additional allocation.

## Example

The following Host snippet demonstrates the call with concrete types; pointers, ranges, and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/ranges>

void example()
{
    using view_type = asc::std::ranges::owning_view<asc::std::ranges::single_view<int>>;
    view_type target{}, source{};
    target = static_cast<view_type&&>(source);
}
```

## Related APIs

- [`asc::std::ranges::owning_view`](ranges_owning_view.md)
- [API list for this header](asc_std_ranges.md)
