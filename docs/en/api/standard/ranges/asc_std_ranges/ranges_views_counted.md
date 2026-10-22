# asc::std::ranges::views::counted

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

`asc::std::ranges::views::counted` builds a bounded subrange from a random-access iterator and a non-negative element count; the range from the start position to the position of the start plus the specified count must be valid.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

This name is a public constant function object; the implementation type of the object does not constitute an interface commitment. The following is the call form; omitted optional arguments follow the constraints of the prototypes.

```cpp
// Excerpt of the declaration inside asc::std::ranges::views; template parameters and other members are provided by the enclosing class.
counted(iterator, count);
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The starting iterator for the fixed-length view to be created. |
| `count` | Input | The number of elements to process, keep, or skip. |

## Return Value

Returns a view starting from the starting iterator that contains the specified number of elements.

| Call form | Return type |
| --- | --- |
| Iterator and count | `subrange<Iterator, Iterator, subrange_kind::sized>` |

## Constraints

- Element access and iteration of the view do not allocate additional storage; the lifetime of the underlying range must cover all uses of the borrowing views.
- The starting iterator must support `first + count`.
- `count` must not be negative, and the elements within the interval must be accessible.

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
    auto view = asc::std::ranges::views::counted(values, 2);
    return view.size() == 2 && *view.begin() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
