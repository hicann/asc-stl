# asc::make_discard_iterator

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

`asc::make_discard_iterator` creates a discard_iterator that discards written values.

## Function Prototype

```cpp
namespace asc {
template <class Integer = asc::std::ptrdiff_t>
constexpr asc::discard_iterator make_discard_iterator(Integer index = 0);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | The index type, defaulting to ptrdiff_t. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The initial index, defaulting to 0: writes are discarded, and the index is used only for position counting and iterator differences. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::discard_iterator` | Returns an iterator adaptor storing the caller's arguments; if the stored function object captures external references, those references must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    auto iterator = asc::make_discard_iterator(0);
    *iterator = 7;
    ++iterator;
    return iterator.index() == 1;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
