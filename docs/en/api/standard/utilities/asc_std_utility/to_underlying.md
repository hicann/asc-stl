# asc::std::to_underlying

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

`asc::std::to_underlying` returns the underlying integer value of an enumeration value.

Standard semantics reference: [cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility).

## Function Prototype

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr underlying_type_t<T> to_underlying(T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The enumeration type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The enumeration value to convert; returns its value converted to the underlying integer type. |

## Return Value

| Return type | Description |
| --- | --- |
| `underlying_type_t<T>` | Returns the underlying integer value of the enumeration value. |

## Constraints

- to_underlying accepts enumeration types only.
- unreachable keeps the standard semantic preconditions but does not add the noreturn attribute, which the current toolchain does not support.

## Example

The following snippet demonstrates the call on this page with concrete values.

```cpp
#include <asc/std/utility>

decltype(auto) example()
{
    enum class code { value = 3 };
    return asc::std::to_underlying(code::value);
}

bool verify_example()
{
    return example() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_utility.md)
