# asc::make_constant_iterator

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

`asc::make_constant_iterator` creates a constant_iterator that always produces the given value.

## Function Prototype

```cpp
namespace asc {
template <class T, class Index = asc::std::ptrdiff_t>
constexpr asc::constant_iterator<T, Index> make_constant_iterator(T value, Index index = 0);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the value the constant iterator stores and returns on each dereference. |
| `Index` | The iterator's internal index type, defaulting to ptrdiff_t: used only for position counting and iterator differences. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The constant value always returned by dereference: reads at any iterator position yield this value. |
| `index` | Input | The initial index, defaulting to 0: it affects only the iterator's position and differences, not the dereference result. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::constant_iterator<T, Index>` | Returns an iterator adaptor storing the caller's arguments; if the stored function object captures external references, those references must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    auto iterator = asc::make_constant_iterator(7);
    ++iterator;
    return *iterator == 7;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
