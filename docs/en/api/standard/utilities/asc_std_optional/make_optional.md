# asc::std::make_optional

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

Header: `<asc/std/optional>`.

`asc::std::make_optional` deduces the type from the given arguments and constructs an engaged optional.

Standard semantics reference: [cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T, class... Args> constexpr asc::std::optional<T> make_optional(Args&&... args);
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> constexpr asc::std::optional<decay_t<T>> make_optional(T&& value);
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The value type to construct; specified explicitly by the caller. |
| `Args` | The list of argument types for in-place construction of T. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `args` | Input/Output | Arguments for in-place construction of T; forwarded in order, and rvalues end up in a valid but unspecified state after being moved. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The type of the value argument; after decay it serves as the element type of the resulting optional. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input/Output | The source of the value contained in the result; lvalues are copied and rvalues are moved, and an rvalue ends up in a valid but unspecified state after being moved. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::optional<T>` | Returns a new state object formed by transforming the current value or error state. |
| Prototype 2 | `asc::std::optional<decay_t<T>>` | Returns a new state object formed by transforming the current value or error state. |

## Constraints

- T must be an ordinary non-reference object type.
- Host follows the valid C++17 operations.
- The operations that construction, assignment, invocation, and swap rely on must not throw on the device side.

## Example

The following snippet demonstrates the call with concrete types; declval is used only in unevaluated type expressions.

```cpp
#include <asc/std/optional>

decltype(auto) example()
{
    return asc::std::make_optional(7);
}

bool verify_example()
{
    const auto result = example();
    return result.has_value() && *result == 7;
}
```

## Related APIs

- [API list for this header](asc_std_optional.md)
