# asc::std::to_integer

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

Header: `<asc/std/cstddef>`.

`asc::std::to_integer` converts a std::byte to the specified integer type.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Function Prototype

```cpp
namespace asc::std {
template<class Integer> constexpr Integer to_integer(byte value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | The integer type to convert to. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The byte value to convert; returns the result of converting its underlying unsigned char value to Integer. |

## Return Value

| Return type | Description |
| --- | --- |
| `Integer` | Returns the value of the specified integer type represented by the current `byte`. |

## Constraints

- The standard declaration is provided.

## Example

The following snippet shows the call on this page with concrete objects.

```cpp
#include <asc/std/cstddef>

decltype(auto) example()
{
    return asc::std::to_integer<unsigned int>(asc::std::byte{7});
}
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
