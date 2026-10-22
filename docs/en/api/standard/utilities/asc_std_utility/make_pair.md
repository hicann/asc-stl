# asc::std::make_pair

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

Header: `<asc/std/utility>`.

`asc::std::make_pair` constructs a pair from two values, applying the specified type decay rules.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T1, class T2> constexpr pair<unwrap_ref_decay_t<T1>, unwrap_ref_decay_t<T2>> make_pair(T1&& left, T2&& right);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T1` | The type of the first element argument; after decay and reference unwrapping it determines the first type of the resulting pair. |
| `T2` | The type of the second element argument; after decay and reference unwrapping it determines the second type of the resulting pair. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input/Output | The source value for constructing the first member; lvalues are copied and rvalues are moved, and an rvalue ends up in a valid but unspecified state after being moved. |
| `right` | Input/Output | The source value for constructing the second member; lvalues are copied and rvalues are moved, and an rvalue ends up in a valid but unspecified state after being moved. |

## Return Value

| Return type | Description |
| --- | --- |
| `pair<unwrap_ref_decay_t<T1>, unwrap_ref_decay_t<T2>>` | Returns a new `pair` object holding the two input values. |

## Constraints

- The exception specification follows the corresponding declaration; element operations used on the device side must not throw.
- The direct free comparison entries for pair are `operator==` and `operator<`; the other relational helpers are in `rel_ops`.

## Example

The following snippet demonstrates the call on this page with concrete values.

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    return asc::std::make_pair(1, 2);
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
