# asc::std::ranges::size

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

`asc::std::ranges::size` obtains the number of elements in a range.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This public name is a constant callable object, not a free function; its implementation class is not part of the public contract. The following only queries the object type, where object_type is an example name. For the call forms, see Parameters and Example.

```cpp
using object_type = decltype(asc::std::ranges::size);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `range` | Input | The input range to be accessed or transformed; the borrowed result is constrained by its lifetime. |

## Return Value

- An array with known bounds returns the array length of type `size_t`.
- The member `size()` or ADL `size` path returns the integer type of that call result after removal of references and top-level cv, which may be a signed type.
- The fallback path using the difference of the start and end iterators returns its unsigned count type. It must not be uniformly assumed that all return values are unsigned.

## Constraints

- An array with known bounds, then an available member size, then ADL size, and finally a difference satisfying forward_iterator and sized_sentinel_for are tried in order.
- disable_sized_range disables the member and ADL branches, and must not be simply understood as disabling all size queries.
- The underlying object must be valid during the call; the result is a count value and does not extend the lifetime of the elements.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

struct example_range { int size() const noexcept { return 3; } };

bool example()
{
    example_range values;
    const auto count = asc::std::ranges::size(values);
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(count)>, int>);
    return count == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
