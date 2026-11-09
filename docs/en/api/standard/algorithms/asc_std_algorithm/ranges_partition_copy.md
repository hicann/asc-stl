# asc::std::ranges::partition_copy

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

Include `<asc/std/algorithm>`. Stably copies into two output ranges according to a predicate on projected elements. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified. Omitted projections use `asc::std::identity`.

```cpp
namespace asc::std::ranges {
partition_copy(first, last, yes, no, pred, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
partition_copy(range, yes, no, pred, projection = {});
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `yes` | Output | Output begin for matching elements. |
| `no` | Output | Output begin for nonmatching elements. |
| `pred` | Input | Predicate invoked on projected elements. |
| `projection` | Input | Projection applied to input elements. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |

## Return Value

`partition_copy_result<Iterator, Output1, Output2>`. in is the input end; out1/out2 are the final positions for elements satisfying/not satisfying the predicate.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Non-borrowed temporaries yield dangling input positions. Positions into borrowed ranges require the underlying storage to remain valid. When a legacy C++17 output adapter does not meet the incrementability constraint, use writable iterators or a C++20 output adapter.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4}, yes[4]{}, no[4]{};
    auto result = asc::std::ranges::partition_copy(values, yes, no, [](int value) { return value % 2 == 0; });
    return result.out1 == yes + 2 && result.out2 == no + 2 && yes[0] == 2 && no[1] == 3;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
