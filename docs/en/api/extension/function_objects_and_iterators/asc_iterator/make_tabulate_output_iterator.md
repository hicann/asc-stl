# asc::make_tabulate_output_iterator

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

`asc::make_tabulate_output_iterator` creates an output iterator that passes the index and value to a function.

## Function Prototype

```cpp
namespace asc {
template <class Function, class Integer = asc::std::ptrdiff_t>
constexpr asc::tabulate_output_iterator<Function, Integer> make_tabulate_output_iterator(
    Function function, Integer index = 0);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Function` | The type of the callable object that performs this page's operation on the input values. |
| `Integer` | The index type, defaulting to ptrdiff_t: it increments as iteration advances and is passed to function. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input | The output function object: assignment to this iterator invokes function(current index, written value). |
| `index` | Input | The starting index, defaulting to 0: it increments with the iterator and serves as the first argument of function. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::tabulate_output_iterator<Function, Integer>` | Returns an iterator adaptor storing the caller's arguments; if the stored function object captures external references, those references must remain valid during use. |

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example uses concrete inputs and checks the result within the object's lifetime.

```cpp
#include <asc/iterator>
bool example()
{
    int values[2] = {};
    auto iterator = asc::make_tabulate_output_iterator([&values](int i, int value) { values[i] = value; }, 0);
    *iterator = 7;
    return values[0] == 7;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
