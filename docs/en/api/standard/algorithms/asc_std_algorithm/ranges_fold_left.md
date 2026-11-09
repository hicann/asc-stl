# asc::std::ranges::fold_left

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

Include `<asc/std/algorithm>`. Accumulates an input range strictly from left to right starting with an initial value. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified.

```cpp
namespace asc::std::ranges {
fold_left(first, last, init, function);
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
fold_left(range, init, function);
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `init` | Input | Initial accumulator passed by value. |
| `function` | Input | Callable performing transformation or accumulation. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |

## Return Value

`decay_t<invoke_result_t<Function&, T, iter_reference_t<Iterator>>>`. An empty range converts the initial value to the result type. The first invocation receives the initial value; later invocations receive the accumulated result.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Initial and result types must be movable and the function copy constructible. The initial type must convert to the decayed first invocation result, and subsequent invocation results must be assignable to it.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3};
    auto result = asc::std::ranges::fold_left(values, 0, [](int total, int value) { return total * 10 + value; });
    return result == 123;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
