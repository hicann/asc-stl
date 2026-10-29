# asc::std::distance

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

Header: `<asc/std/iterator>`.

`asc::std::distance` computes the distance between two iterators.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class InputIter> constexpr typename iterator_traits<InputIter>::difference_type distance(InputIter first, InputIter last);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIter` | The iterator type used to read the elements of the input range; it must satisfy the traversal capabilities required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The start iterator or pointer of the input range. |
| `last` | Input | The end position of the input range, exclusive of that position. |

## Return Value

| Return type | Description |
| --- | --- |
| `typename iterator_traits<InputIter>::difference_type` | Returns the computed distance between the two iterators. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host snippet demonstrates the call with a concrete array or an explicit container; the iterator must remain within the valid range.

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::distance(values, values + 4);
}

bool verify_example()
{
    return example() == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
