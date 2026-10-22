# asc::std::apply

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

`asc::std::apply` expands tuple elements as arguments of a function object and invokes it.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
template<class Function, class Tuple> constexpr decltype(auto) apply(Function&& function, Tuple&& value);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Function` | The callable object type that receives the expanded tuple-like elements. |
| `Tuple` | The tuple-like argument type that provides tuple_size and get. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `function` | Input/Output | The callable object to be invoked; the elements of the tuple are expanded in order as its arguments (invoked with invoke semantics), and its call result is returned. |
| `value` | Input/Output | The tuple object expanded for the call; its elements serve in order as the call arguments, rvalue elements are moved, and moved-from elements are in a valid but unspecified state. |

## Return Value

| Return type | Description |
| --- | --- |
| `decltype(auto)` | Returns the result of invoking the function object with the tuple elements expanded. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto values = asc::std::make_tuple(2, 3);
    return asc::std::apply([](int left, int right) { return left + right; }, values) == 5;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
