# asc::make_transform_input_output_iterator

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

`asc::make_transform_input_output_iterator` creates an iterator with both an input transform and an output transform.

## Function Prototype

```cpp
namespace asc {
template <class Iterator, class InputFunction, class OutputFunction>
constexpr asc::transform_input_output_iterator<InputFunction, OutputFunction, Iterator>
make_transform_input_output_iterator(Iterator iterator, InputFunction input_function, OutputFunction output_function);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iterator` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |
| `InputFunction` | The type of the callable read-transform object: reads are transformed as input_function(*underlying iterator). |
| `OutputFunction` | The type of the callable write-transform object: writes are first transformed by output_function and then stored into the underlying iterator. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterator` | Input | The underlying iterator to be wrapped: reads and writes actually act on the position this iterator points to. |
| `input_function` | Input | The read transform object: the dereference read result is input_function(*underlying iterator). |
| `output_function` | Input | The write transform object: values assigned to this iterator are first transformed by output_function and then written to the underlying position. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::transform_input_output_iterator<InputFunction, OutputFunction, Iterator>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |

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
    auto iterator = asc::make_transform_input_output_iterator(
        values, [](int value) { return value; }, [](int value) { return value; });
    *iterator = 9;
    return (*iterator).read() == 9 && values[0] == 9;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
