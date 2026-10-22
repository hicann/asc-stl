# asc::std::make_reverse_iterator

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

`asc::std::make_reverse_iterator` creates an iterator adaptor that traverses in reverse order.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

```cpp
namespace asc::std {
template<class Iter> constexpr reverse_iterator<Iter> make_reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iter` | The base iterator type being adapted; it must at least satisfy the bidirectional iterator requirements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The wrapped base iterator; usually the past-the-end iterator of a range is passed, and the adaptor traverses backward from that position in reverse order. |

## Return Value

| Return type | Description |
| --- | --- |
| `reverse_iterator<Iter>` | Returns the iterator adaptor that stores the caller's arguments; the underlying range must remain valid while in use. |

## Constraints

- The underlying iterator must support bidirectional traversal; random-access members additionally require the underlying iterator to support the corresponding offset or subscript operations.
- The reverse iterator accesses the element before `base()`; dereference or arrow access requires that previous position to be valid.
- The adaptor does not own the underlying range; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::make_reverse_iterator(values + 4);
    return result.base() == values + 4 && *result == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
