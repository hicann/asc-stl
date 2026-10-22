# asc::std::ranges::ref_view::base

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

`asc::std::ranges::ref_view::base` returns the underlying iterator or object stored by the adaptor.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Function Prototype

Member of: [`asc::std::ranges::ref_view`](ranges_ref_view.md).

```cpp
// Excerpt of the declaration inside the asc::std::ranges::ref_view class; template parameters and other members are provided by the enclosing class.
constexpr Range& base() const;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `Range &` | Returns the underlying iterator or object stored by the adaptor. |

## Constraints

- Element access and iteration on the view do not allocate additional storage; the underlying range's lifetime must cover all uses of borrowed views.

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
    asc::std::ranges::ref_view<int[4]> view(values);
    return *asc::std::ranges::begin(view.base()) == 1;
}
```

## Related APIs

- [`asc::std::ranges::ref_view`](ranges_ref_view.md)
- [API list for this header](asc_std_ranges.md)
