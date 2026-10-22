# asc::std::make_move_iterator

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

`asc::std::make_move_iterator` creates an iterator adaptor that accesses elements by rvalue reference on dereference.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class Iter> constexpr move_iterator<Iter> make_move_iterator(Iter iterator) noexcept(is_nothrow_move_constructible_v<Iter>);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iter` | The underlying iterator type being wrapped or moved. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The iterator that points to the position for this operation; the pointed-to range must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `move_iterator<Iter>` | Returns the iterator adaptor that stores the caller's arguments; the underlying range must remain valid while in use. |

## Constraints

- The underlying iterator must support the operations on this page; decrement requires bidirectional traversal, and offsets and subscripts require the corresponding random-access operations.
- The adaptor does not own the underlying elements; dereference accesses the element through `asc::std::iter_move`, and moved-from values follow the conventions of the element type.
- Dereference, arrow, and subscript access must point to valid elements; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::make_move_iterator(values);
    return result.base() == values && *result == 1;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
