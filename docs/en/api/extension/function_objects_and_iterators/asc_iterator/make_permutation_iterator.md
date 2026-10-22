# asc::make_permutation_iterator

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

Header: `<asc/iterator>`.

`asc::make_permutation_iterator` creates a permutation_iterator that accesses data following an index sequence.

## Function Prototype

```cpp
namespace asc {
template <class Iterator, class IndexIterator>
constexpr asc::permutation_iterator<Iterator, IndexIterator> make_permutation_iterator(
    Iterator iterator, IndexIterator index);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iterator` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |
| `IndexIterator` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The iterator pointing to the position of this operation; the range it points to must remain valid during the call. |
| `index` | Input | The iterator pointing to the position of this operation; the range it points to must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::permutation_iterator<Iterator, IndexIterator>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    int indices[4] = {3, 2, 1, 0};
    auto iterator = asc::make_permutation_iterator(values, indices);
    return *iterator == 4;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
