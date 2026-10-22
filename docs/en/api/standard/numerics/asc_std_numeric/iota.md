# asc::std::iota

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

Header: `<asc/std/numeric>`.

`asc::std::iota` fills a range with consecutive values starting from the given starting value.

Standard semantics reference: [cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric).

## Function Prototype

```cpp
namespace asc::std {
template<class ForwardIterator, class T> constexpr void iota(ForwardIterator first, ForwardIterator last, T value_);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ForwardIterator` | The iterator type of the range to fill; must support writing the pointed-to elements and traversing forward. |
| `T` | The type of the starting fill value; after increment it must be assignable to the range elements, and the two types may differ; must support ++ increment. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Input | The starting iterator of the range to fill. |
| `last` | Input | The past-the-end iterator of the range to fill, exclusive. |
| `value_` | Input | The starting fill value; after being written to the first element, it is incremented once for each advance and written to subsequent elements. |

## Return Value

No return value.

## Constraints

- `[first, last)` must be a valid writable forward iterator range.
- After assigning the current `value` to an element, `++value` is executed; the type must support assignment and pre-increment, and the required increment operations must be valid.

## Example

The following example fills the four output elements with 1, 2, 3, 4 in order.

```cpp
#include <asc/std/numeric>

bool example()
{
    int output[4] = {};
    asc::std::iota(output, output + 4, 1);
    return output[0] == 1 && output[1] == 2 && output[2] == 3 && output[3] == 4;
}
```

## Related APIs

- [API list for this header](asc_std_numeric.md)
