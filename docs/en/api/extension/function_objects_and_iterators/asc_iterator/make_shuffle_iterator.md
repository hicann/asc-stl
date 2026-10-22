# asc::make_shuffle_iterator

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

`asc::make_shuffle_iterator` creates a shuffle_iterator that permutes the access order according to a deterministic mapping.

## Function Prototype

```cpp
namespace asc {
template <class Bijection, class Index = asc::std::size_t>
constexpr asc::shuffle_iterator<Index, Bijection> make_shuffle_iterator(Bijection bijection, Index start = 0);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Bijection` | The type of the deterministic mapping object: it takes the current index as input and computes the permuted access result. |
| `Index` | The index type of the iterator's internal cursor, defaulting to size_t. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `bijection` | Input | The deterministic mapping object: dereference and subscript yield bijection(current index). |
| `start` | Input | The cursor's starting index, defaulting to 0: it increments as iteration advances and is the input to bijection. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::shuffle_iterator<Index, Bijection>` | Returns an iterator adaptor storing the caller's arguments; if the stored function object captures external references, those references must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    auto iterator = asc::make_shuffle_iterator([](unsigned index) { return index + 1; }, 0u);
    ++iterator;
    return *iterator == 2u;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
