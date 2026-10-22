# asc::std::ranges::views::single

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

`asc::std::ranges::views::single` creates a view containing a single value.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This name is a public constant function object; the implementation type of the object does not constitute an interface commitment. The following is the call form; omitted optional arguments follow the constraints of the prototypes.

```cpp
// Excerpt of the declaration inside asc::std::ranges::views; template parameters and other members are provided by the enclosing class.
single(value);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value used to construct the view or fill the range. |

## Return Value

Returns a view containing only the given value.

| Call form | Return type |
| --- | --- |
| Single value | `single_view<decay_t<T>>` |

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
    auto view = asc::std::ranges::views::single(7);
    return view.size() == 1 && *view.begin() == 7;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
