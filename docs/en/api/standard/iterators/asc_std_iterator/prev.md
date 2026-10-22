# asc::std::prev

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

`asc::std::prev` returns the iterator moved backward by the specified distance.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class InputIter> constexpr InputIter prev(InputIter value, typename iterator_traits<InputIter>::difference_type count = 1);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIter` | The bidirectional iterator type (it must support decrement stepping when count is positive). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The iterator to be moved backward (passed by value and not modified); returns a copy moved count steps backward. |
| `count` | Input | The number of steps to move backward (difference_type), defaulting to 1; a negative value means moving forward. |

## Return Value

| Return type | Description |
| --- | --- |
| `InputIter` | Returns the position moved by the specified distance; whether the original iterator is modified is determined by the corresponding prototype. |

## Constraints

- Supports non-I/O ranges, arrays, and user containers.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::prev(values + 4, 2);
    return result == values + 2 && *result == 3;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
