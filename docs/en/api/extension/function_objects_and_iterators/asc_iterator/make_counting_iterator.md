# asc::make_counting_iterator

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

`asc::make_counting_iterator` creates a counting_iterator starting from the given initial value.

## Function Prototype

```cpp
namespace asc {
template <class Start>
constexpr asc::counting_iterator<Start> make_counting_iterator(Start start);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Start` | The type of the values the counter produces: dereference and subscript return a count of this type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `start` | Input | The starting count: dereference produces this value, and it increments step by step as the iterator advances. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::counting_iterator<Start>` | Returns an iterator adaptor storing the caller's arguments; if the stored function object captures external references, those references must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    auto iterator = asc::make_counting_iterator(3);
    ++iterator;
    return *iterator == 4;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
