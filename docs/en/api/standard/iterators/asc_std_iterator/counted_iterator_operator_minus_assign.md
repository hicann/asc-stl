# asc::std::counted_iterator::`operator-=`

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

`asc::std::counted_iterator::operator-=` updates the current value in reverse by the given distance or operand.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::counted_iterator`](counted_iterator.md).

```cpp
// Excerpt of the declaration inside counted_iterator; the class template parameters and the remaining members are provided by the enclosing class.
template<class I2 = Iter, enable_if_t<random_access_iterator<I2>, int> = 0>
constexpr counted_iterator& operator-=(iter_difference_t<I2> count);
```

The above are the C++17 and Device selection forms; Host C++20 expresses the same participation condition with `requires random_access_iterator<I2>`.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `I2` | The member selection type, defaulting to the enclosing class's `Iter`; it must satisfy the expression or traversal requirements of this prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | The number of elements participating in the operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `counted_iterator<Iter> &` | Returns a reference to the updated current object; assignment or compound operations can continue on it. |

## Constraints

- `Iter` must satisfy the traversal capabilities required by this operation; the adaptor does not own the underlying range.
- `count()` gives the number of elements remaining from the current position; dereference and increment require the remaining count to be greater than 0.
- The underlying position after the shift and the corresponding count must be valid and must not go beyond the actually valid range.
- The shift or subscript members on this page require the underlying iterator to satisfy the random-access iterator requirements.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::counted_iterator<int*> iterator(values + 1, 3);
    auto& result = (iterator -= 1);
    return &result == &iterator && *iterator == 2;
}
```

## Related APIs

- [`asc::std::counted_iterator`](counted_iterator.md)
- [API list for this header](asc_std_iterator.md)
