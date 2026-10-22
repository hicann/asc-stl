# asc::std::make_from_tuple

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

Header: `<asc/std/tuple>`.

`asc::std::make_from_tuple` creates an object of the specified type with the tuple elements as construction arguments.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
template<class T, class Tuple> constexpr T make_from_tuple(Tuple&& value);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The target type to be constructed; must be constructible with the tuple elements as construction arguments. |
| `Tuple` | The tuple-like type providing the construction arguments. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The tuple providing the construction arguments; its elements serve in order as the construction arguments of T, the elements are moved when it is an rvalue, and moved-from elements are in a valid but unspecified state. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the object of the target type constructed with the tuple elements. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

struct point {
    int x, y;
    point(int first, int second) : x(first), y(second) {}
};

bool example()
{
    const auto args = asc::std::make_tuple(2, 3);
    const auto value = asc::std::make_from_tuple<point>(args);
    return value.x == 2 && value.y == 3;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
