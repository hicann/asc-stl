# asc::std::ranges::views::all

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

`asc::std::ranges::views::all` converts an input range into an appropriate non-owning or owning view.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This public name is a constant callable object, not a free function; its implementation class is not part of the public contract. The following only queries the object type, where object_type is an example name. For the call forms, see Parameters and Example.

```cpp
using object_type = decltype(asc::std::ranges::views::all);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; the borrowed result is constrained by its lifetime. |

## Return Value

| Input condition (selected in order) | Result |
| --- | --- |
| Already a view after removing cv/ref, and constructible from the input | Copies or moves that view type by value; borrowability is determined by the view itself. |
| Other inputs that can be associated by ref_view | ref_view, typically an lvalue of an external range; it does not take ownership of the elements. |
| Other inputs satisfying viewable_range that can be stored by owning_view | owning_view, storing the moved range object; whether that object owns the elements still depends on the underlying range type. |

## Constraints

- The input must satisfy viewable_range; the selection follows the priority above, and ownership must not be judged merely by lvalue/rvalue.
- An rvalue ref_view still borrows the original range; copying a non-owning view does not copy the underlying elements and does not extend their lifetime.
- All borrowed storage must cover the actual access periods of the view and its iterators.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>
#include <asc/std/utility>

bool example()
{
    int values[3] = {1, 2, 3};
    auto original = asc::std::ranges::views::all(values);
    auto copied = asc::std::ranges::views::all(original);
    auto moved = asc::std::ranges::views::all(asc::std::move(original));
    static_assert(asc::std::is_same_v<decltype(copied), decltype(moved)>);
    return copied.data() == values && moved.data() == values && moved.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
