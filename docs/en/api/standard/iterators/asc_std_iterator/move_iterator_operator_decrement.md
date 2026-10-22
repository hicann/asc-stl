# asc::std::move_iterator::`operator--`

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

`asc::std::move_iterator::operator--` moves the current iterator or count one step backward.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::move_iterator`](move_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::std::move_iterator; template parameters and other members are provided by the enclosing class.
constexpr move_iterator<Iter>& operator--();
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::std::move_iterator; template parameters and other members are provided by the enclosing class.
constexpr move_iterator<Iter> operator--(int unused);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `unused` | Input | A placeholder parameter used to distinguish the postfix increment or postfix decrement form; written as the integer 0 at the call site. |

## Return Value

The prefix form returns a reference to the current adaptor after the operation completes; the postfix form returns a copy of the adaptor as it was before the operation by value.

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
    int values[] = {2, 4, 6, 8};
    asc::std::move_iterator<int*> iterator(values + 1);
    auto old = iterator--;
    return *old == 4 && *iterator == 2;
}
```

## Related APIs

- [`asc::std::move_iterator`](move_iterator.md)
- [API list for this header](asc_std_iterator.md)
