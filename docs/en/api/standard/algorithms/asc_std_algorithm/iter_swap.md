# asc::std::iter_swap

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

Headers: `<asc/std/algorithm>`, `<asc/std/iterator>`.

`asc::std::iter_swap` swaps the elements pointed to by two iterators; it executes sequentially within the execution entity of the caller.

Standard semantics reference: [cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm).

## Function Prototype

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
constexpr auto iter_swap(ForwardIterator1 left, ForwardIterator2 right) noexcept(
    noexcept(swap(*left, *right))) -> decltype(void(swap(*left, *right)));
}  // namespace asc::std
```

This prototype corresponds to the headers `<asc/std/algorithm>`, `<asc/std/iterator>`.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator1` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |
| `ForwardIterator2` | Iterator type used to traverse the input range; must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Iterator pointing to the position of this operation; the range it points to must remain valid during the call. |
| `b` | Input | Iterator pointing to the position of this operation; the range it points to must remain valid during the call. |

## Return Value

No return value.

## Constraints

- Provides overloads that execute sequentially and perform no dynamic memory allocation.
- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host snippet demonstrates the call with a valid integer range and an output buffer with sufficient capacity.

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::iter_swap(values, values + 1);
    return values[0] == 3 && values[1] == 8 && values[2] == 6;
}
```

## Related APIs

- [API list for this header](asc_std_algorithm.md)
