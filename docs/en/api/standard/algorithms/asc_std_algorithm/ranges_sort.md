# asc::std::ranges::sort

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

Include `<asc/std/algorithm>`. Sorts a random-access range in place using a comparator and projection. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified. Omitted projections use `asc::std::identity`; sorting defaults to `asc::std::ranges::less`.

```cpp
namespace asc::std::ranges {
sort(first, last, compare = {}, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
sort(range, compare = {}, projection = {});
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `compare` | Input | Comparator defining a strict weak ordering. |
| `projection` | Input | Projection applied to input elements. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |

## Return Value

`Iterator / borrowed_iterator_t<Range>`. Returns the end iterator; relative order of equivalent elements is unspecified.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Non-borrowed temporaries yield dangling input positions. Positions into borrowed ranges require the underlying storage to remain valid. Requires sortable random-access iterators.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {3, 1, 4};
    auto result = asc::std::ranges::sort(values);
    return result == values + 3 && values[0] == 1 && values[1] == 3 && values[2] == 4;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
