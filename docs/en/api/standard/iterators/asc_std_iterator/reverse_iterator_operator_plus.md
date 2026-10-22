# asc::std::reverse_iterator::`operator+`

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

`asc::std::reverse_iterator::operator+` produces a new value according to the addition or offset rules defined by this type.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::reverse_iterator`](reverse_iterator.md).

```cpp
// Excerpt of the declaration inside asc::std::reverse_iterator; template parameters and other members are provided by the enclosing class.
constexpr reverse_iterator<Iter> operator+(difference_type count) const;
```

### Symmetric non-member form

```cpp
friend constexpr reverse_iterator operator+(difference_type count, const reverse_iterator& value);
```

This is a hidden friend declaration inside the reverse_iterator<Iter> class, called as count+value; it is not a member function.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | The number of elements involved in the operation. |

In the symmetric form, count is a signed distance and value is a const reference to the source adaptor; it returns a new adaptor equal to value+count and does not change value. The underlying iterator must support the corresponding random-access offset.

## Return Value

| Return type | Description |
| --- | --- |
| `reverse_iterator<Iter>` | Returns the new iterator moved by the specified distance; the original iterator remains unchanged. |

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
    int values[] = {2, 4, 6, 8};
    asc::std::reverse_iterator<int*> iterator(values + 4);
    auto result = iterator + 1;
    auto symmetric = 1 + iterator;
    return *result == 6 && *iterator == 8 && symmetric.base() == result.base();
}
```

## Related APIs

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [API list for this header](asc_std_iterator.md)
