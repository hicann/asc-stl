# asc::make_zip_iterator

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

`asc::make_zip_iterator` creates a zip_iterator that advances multiple underlying iterators in parallel.

## Function Prototype

```cpp
namespace asc {
template <class... Iterators>
constexpr asc::zip_iterator<Iterators...> make_zip_iterator(Iterators... iterators);
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Iterators` | The type of iterator used to traverse the input range; it must satisfy the traversal capability required by the prototype. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `iterators` | Input | The iterators pointing to the positions of this operation; the ranges they point to must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::zip_iterator<Iterators...>` | Returns an iterator adaptor storing the caller's arguments; the underlying range must remain valid during use. |

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
    auto iterator = asc::make_zip_iterator(values, indices);
    return (*iterator).get<0>() == 1 && (*iterator).get<1>() == 3;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
