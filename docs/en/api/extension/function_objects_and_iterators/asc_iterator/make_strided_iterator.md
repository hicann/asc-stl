# asc::make_strided_iterator

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

`asc::make_strided_iterator` constructs a fixed-stride adaptor from an underlying random access iterator; the single-argument overload uses stride 1, and the two-argument overload uses the given positive or negative non-zero stride.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <class Iterator, class Stride>
constexpr asc::strided_iterator<Iterator, Stride> make_strided_iterator(Iterator iterator, Stride stride);
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <class Iterator>
constexpr asc::strided_iterator<Iterator> make_strided_iterator(Iterator iterator);
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iterator` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |
| `Stride` | The stride type (an integer type). |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The underlying iterator to be wrapped: each time this iterator advances 1 step, the underlying iterator advances stride positions. |
| `stride` | Input | The number of underlying elements spanned per step: advancing/retreating 1 step moves the underlying iterator by stride positions; it must be non-zero. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iterator` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The underlying iterator to be wrapped: this prototype is the degenerate form with stride 1 and accesses with unit stride. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::strided_iterator<Iterator, Stride>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |
| Prototype 2 | `asc::strided_iterator<Iterator>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |

## Constraints

- The underlying iterator must support random access, and the stride must be a non-zero integer.
- The returned object does not own the underlying range.
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
    auto iterator = asc::make_strided_iterator(values, 2);
    return *iterator == 1 && iterator[1] == 3;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
