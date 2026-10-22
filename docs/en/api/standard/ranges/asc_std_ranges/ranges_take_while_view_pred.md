# asc::std::ranges::take_while_view::pred

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

`asc::std::ranges::take_while_view::pred` returns the predicate object stored in the current view.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`asc::std::ranges::take_while_view`](ranges_take_while_view.md).

```cpp
// Excerpt of the declaration inside asc::std::ranges::take_while_view; template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr const Pred& pred() const;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `const Pred &` | Returns the predicate object stored in the current view. |

## Constraints

- Element access and iteration of the view do not allocate additional storage; the lifetime of the underlying range must cover all uses of the borrowing views.

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
    auto predicate = [](int value) { return value < 3; };
    asc::std::ranges::take_while_view<Base, decltype(predicate)> view(base, predicate);
    return view.pred()(2) && !view.pred()(3);
}
```

## Related APIs

- [`asc::std::ranges::take_while_view`](ranges_take_while_view.md)
- [API list for this header](asc_std_ranges.md)
