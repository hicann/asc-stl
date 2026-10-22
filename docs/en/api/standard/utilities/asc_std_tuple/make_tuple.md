# asc::std::make_tuple

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

`asc::std::make_tuple` constructs a tuple from the arguments according to the type decay rules.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Function Prototype

```cpp
namespace asc::std {
template<class ...T> [[nodiscard]] constexpr tuple<unwrap_ref_decay_t<T>...> make_tuple(T&&... values) noexcept(is_nothrow_constructible_v<tuple<unwrap_ref_decay_t<T>...>, T...>);
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The types of the arguments; after decay and reference unwrapping they determine the corresponding element type of the result tuple. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `values` | Input/Output | The arguments that construct the result tuple; they are copied or moved into the result by value semantics, and moved-from arguments are in a valid but unspecified state. |

## Return Value

| Return type | Description |
| --- | --- |
| `tuple<unwrap_ref_decay_t<T>...>` | Returns the new tuple composed from the given elements or tuples. |

## Constraints

- The utility itself allocates no additional container storage; element construction, assignment, swapping, or passing into a callable body may still allocate or throw according to their own semantics, so the whole call is not guaranteed to be allocation-free on this basis.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

bool example()
{
    const auto left = asc::std::make_tuple(2, 3);
    return asc::std::get<0>(left) == 2 && asc::std::get<1>(left) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
