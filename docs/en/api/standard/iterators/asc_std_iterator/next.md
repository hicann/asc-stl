# asc::std::next

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

`asc::std::next` returns the iterator advanced forward by the specified distance.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class InputIterator> constexpr InputIterator next(InputIterator x, asc::std::iter_difference_t<InputIterator> n = 1);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `InputIterator` | The iterator type for reading the elements of the input range; it must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | The iterator that points to the position for this operation; the pointed-to range must remain valid during the call. |
| `n` | Input | The distance to move, defaulting to 1; a negative value requires the underlying iterator to support valid bidirectional retreat. |

## Return Value

| Return type | Description |
| --- | --- |
| `InputIterator` | Returns the position moved by the specified distance; whether the original iterator is modified is determined by the corresponding prototype. |

## Constraints

- `n` is a signed move distance; a negative value requires a bidirectional iterator, and the positions passed over during the move must be valid.
- The returned iterator does not own the range; the pointed-to objects must remain valid while in use.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::next(values, 2);
    return result == values + 2 && *result == 3;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
