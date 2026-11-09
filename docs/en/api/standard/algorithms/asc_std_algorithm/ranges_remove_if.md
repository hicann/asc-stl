# asc::std::ranges::remove_if

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

Include `<asc/std/algorithm>`. Stably compacts elements not satisfying the projected predicate by move assignment and returns the trailing subrange. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified. Omitted projections use `asc::std::identity`.

```cpp
namespace asc::std::ranges {
remove_if(first, last, pred, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
remove_if(range, pred, projection = {});
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `pred` | Input | Predicate invoked on projected elements. |
| `projection` | Input | Projection applied to input elements. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |

## Return Value

`subrange<Iterator> / borrowed_subrange_t<Range>`. The returned begin is the new logical end and end is the original end. Container size is unchanged.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Non-borrowed temporaries yield dangling input positions. Positions into borrowed ranges require the underlying storage to remain valid. Requires permutable forward iterators; values in the trailing subrange are unspecified.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto tail = asc::std::ranges::remove_if(values, [](int value) { return value % 2 == 0; });
    return tail.begin() == values + 2 && tail.end() == values + 4 && values[0] == 1 && values[1] == 3;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
