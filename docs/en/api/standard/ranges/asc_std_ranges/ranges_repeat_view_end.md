# asc::std::ranges::repeat_view::end

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

`asc::std::ranges::repeat_view::end` returns an iterator to the position past the end.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`asc::std::ranges::repeat_view`](ranges_repeat_view.md).

```cpp
// Excerpt of the declaration inside asc::std::ranges::repeat_view; template parameters and other members are provided by the enclosing class.
constexpr auto end() const noexcept(is_nothrow_copy_constructible_v<Bound>);
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns an iterator to the position past the end. |

## Constraints

- Seven names are listed.
- Bounded repeat, two-way random-access+sized zip reference write-back, single range|closure.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

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
    asc::std::ranges::repeat_view<int, int> view(7, 3);
    auto last = view.end();
    unsigned int count = 0;
    for (auto it = view.begin(); it != last; ++it) ++count;
    return count == 3;
}
```

## Related APIs

- [`asc::std::ranges::repeat_view`](ranges_repeat_view.md)
- [API list for this header](asc_std_ranges.md)
