# asc::std::ranges::for_each_n

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

Header: `<asc/std/algorithm>`.

`asc::std::ranges::for_each_n` invokes the function on a specified number of elements one by one, available since C++17, with support for projections; it returns the end iterator and the function object after the calls.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Declaration

This name is a public constant function object; the object's implementation type is not part of the interface commitment. The following are the call forms; omitted optional parameters are governed by the constraints of each prototype.

```cpp
namespace asc::std::ranges {
for_each_n(first, count, function, projection);
}  // namespace asc::std::ranges
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | Iterator to the start of the input range. |
| `count` | Input | Number of elements to process; when non-positive, the function is not invoked and the start iterator is retained. |
| `function` | Input | Callable object that performs an operation on each input element. |
| `projection` | Input | Projection function applied to elements before comparison or evaluation; when omitted, `asc::std::identity` is used. |

## Return Value

Returns a result object containing the iterator after processing the specified number of elements and the function object after the calls.

| Call form | Return type |
| --- | --- |
| Iterator and count | `for_each_n_result<Iterator, Function>` |

## Constraints

- When `count` is positive, there must be at least `count` valid elements after the start position; when `count` is non-positive, the range is not accessed.
- The function object must be able to accept projected elements.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto action = [](int& value) { ++value; };
    auto result = asc::std::ranges::for_each_n(values, 4, action);
    auto empty_result = asc::std::ranges::for_each_n(values, -4, action);
    return result.in == values + 4 && empty_result.in == values && values[0] == 2 && values[3] == 5;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
