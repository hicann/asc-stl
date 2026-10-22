# asc::make_zip_transform_iterator

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

`asc::make_zip_transform_iterator` creates a zip_transform_iterator that invokes a function on multiple inputs at dereference.

## Function Prototype

```cpp
namespace asc {
template <class Function, class... Iterators>
constexpr asc::zip_transform_iterator<Function, Iterators...> make_zip_transform_iterator(
    Function function, Iterators... iterators);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Function` | The type of the callable object that performs this page's operation on the input values. |
| `Iterators` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input | The combining function object: on dereference it expands the references of the underlying iterators and evaluates function(*it0, *it1, ...). |
| `iterators` | Input | The underlying iterators to be zipped (zero or more): they advance in lockstep in zip-iterator fashion. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::zip_transform_iterator<Function, Iterators...>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |

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
    auto iterator = asc::make_zip_transform_iterator([](int left, int right) { return left + right; }, values, indices);
    return *iterator == 4;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
