# asc::std::ranges::ssize

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

`asc::std::ranges::ssize(range)` reads the range size and converts it to a signed integer; both lvalues and rvalues satisfying the size call conditions can be passed in.

## Declaration

This public name is a constant callable object, not a free function; its implementation class is not part of the public contract. The following only queries the object type, where object_type is an example name. For the call forms, see Parameters and Example.

```cpp
using object_type = decltype(asc::std::ranges::ssize);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; the borrowed result is constrained by its lifetime. |

## Return Value

Let `SignedSize = make_signed_t<decltype(ranges::size(range))>`. Returns `ptrdiff_t` when `sizeof(ptrdiff_t) > sizeof(SignedSize)`, otherwise returns `SignedSize`. The result only holds the count and does not borrow the range.

## Constraints

- For a range object passed by forwarding, calling `ranges::size` on the named lvalue must be valid; it accepts both lvalues and rvalues satisfying the conditions.
- The signed result must be able to represent the count; the query does not return element references, and the range object does not need to cover the subsequent use of the integer result.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>
#include <asc/std/cstddef>

struct example_range {
    unsigned char size() const noexcept { return 3; }
};

bool example()
{
    const auto count = asc::std::ranges::ssize(example_range{});
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(count)>, asc::std::ptrdiff_t>);
    return count == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
