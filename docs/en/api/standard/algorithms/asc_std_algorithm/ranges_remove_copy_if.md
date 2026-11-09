# asc::std::ranges::remove_copy_if

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

Include `<asc/std/algorithm>`. Stably copies elements not satisfying the projected predicate, preserving the input. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified. Omitted projections use `asc::std::identity`.

```cpp
namespace asc::std::ranges {
remove_copy_if(first, last, output, predicate, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
remove_copy_if(range, output, predicate, projection = {});
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `output` | Output | Output begin position. |
| `predicate` | Input | Predicate invoked on projected elements. |
| `projection` | Input | Projection applied to input elements. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |

## Return Value

`remove_copy_if_result<Iterator, Output>`. The result contains the input end in and final output position out.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Non-borrowed temporaries yield dangling input positions. Positions into borrowed ranges require the underlying storage to remain valid. When a legacy C++17 output adapter does not meet the incrementability constraint, use writable iterators or a C++20 output adapter.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4}, output[4]{};
    auto result = asc::std::ranges::remove_copy_if(values, output, [](int value) { return value % 2 == 0; });
    return result.out == output + 2 && output[0] == 1 && output[1] == 3 && values[1] == 2;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
