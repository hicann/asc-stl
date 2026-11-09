# asc::std::ranges::in_in_out_result

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

Include `<asc/std/algorithm>`. Stores input and output positions returned by range algorithms without owning the underlying storage.

## Declaration

The class declaration excerpt shows result fields only; field attributes and conversion operators are omitted.

```cpp
namespace asc::std::ranges {
template <class Input1, class Input2, class Output>
struct in_in_out_result {
    Input1 in1;
    Input2 in2;
    Output out;
};
}  // namespace asc::std::ranges
```

## Parameters

| Field | Meaning |
| --- | --- |
| `in1` | Input position. |
| `in2` | Input position. |
| `out` | Output position. |

## Constraints

When each field is convertible, the result can be converted by copying an lvalue or moving an rvalue. Stored pointers and iterators extend no lifetime; input positions from non-borrowed temporary ranges are dangling.

## Example

```cpp
#include <asc/std/algorithm>

bool example()
{
    int source[1]{}, output[1]{};
    asc::std::ranges::in_in_out_result<int*, int*, int*> result{source, source, output};
    return result.in1 == source && result.in2 == source && result.out == output;
}
```

## Related APIs

- [<asc/std/algorithm>](asc_std_algorithm.md)
