# asc::std::ranges::transform

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

Include `<asc/std/algorithm>`. Applies a unary or binary operation to projected inputs and writes the output. Provided as a constant callable object available since C++17.

## Declaration

The following are the delivered call forms; the object implementation type is unspecified. Omitted projections use `asc::std::identity`.

```cpp
namespace asc::std::ranges {
transform(first, last, out, function, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(range, out, function, projection = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(first1, last1, first2, last2, output, function, projection1 = {}, projection2 = {});
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
transform(range1, range2, output, function, projection1 = {}, projection2 = {});
}  // namespace asc::std::ranges
```

## Parameters

| Name | Direction | Description |
| --- | --- | --- |
| `first` | Input | Input begin iterator. |
| `last` | Input | Input end sentinel. |
| `out` | Output | Output begin position. |
| `function` | Input | Callable performing transformation or accumulation. |
| `projection` | Input | Projection applied to input elements. |
| `range` | Input | Range to access; non-owning results depend on its lifetime. |
| `first1` | Input | First input begin iterator. |
| `last1` | Input | First input end sentinel. |
| `first2` | Input | Second input begin iterator. |
| `last2` | Input | Second input end sentinel. |
| `output` | Output | Output begin position. |
| `projection1` | Input | First input projection. |
| `projection2` | Input | Second input projection. |
| `range1` | Input | First input range. |
| `range2` | Input | Second input range. |

## Return Value

`unary_transform_result<Iterator, Output> / binary_transform_result<Iterator1, Iterator2, Output>`. Unary results contain in/out; binary results contain in1/in2/out. Binary transformation stops at the shorter input.

## Constraints

Iterator/sentinel pairs must form valid ranges and output storage must be sufficient. Callables, projections, writes and moves must meet the algorithm type constraints. The interface owns no storage, extends no lifetime and provides no inter-thread device synchronization. Non-borrowed temporaries yield dangling input positions. Positions into borrowed ranges require the underlying storage to remain valid. When a legacy C++17 output adapter does not meet the incrementability constraint, use writable iterators or a C++20 output adapter.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int left[] = {1, 2, 3}, right[] = {4, 5}, output[3]{};
    auto result = asc::std::ranges::transform(left, right, output, [](int x, int y) { return x + y; });
    return result.in1 == left + 2 && result.in2 == right + 2 && result.out == output + 2 && output[0] == 5 && output[1] == 7;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
