# asc::std::bit_cast

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

Header: `<asc/std/bit>`.

`asc::std::bit_cast` copies the object representation and obtains a value of the target type when the size and trivially copyable constraints are satisfied.

Standard semantics reference: [cppreference `bit`](https://en.cppreference.com/w/cpp/header/bit).

## Function Prototype

```cpp
namespace asc::std {
template<class To, class From> [[nodiscard]] constexpr To bit_cast(const From& fx) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `To` | Target type of the bit conversion; must be trivially copyable and the same size as the source type. |
| `From` | Source type of the bit conversion; must be trivially copyable and the same size as the target type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `fx` | Input | Provides the object reference used to "copy the object representation and obtain a value of the target type when the size and trivially copyable constraints are satisfied"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `To` | Returns a new value of the target type with the same object representation. |

## Constraints

- `To` and `From` must satisfy `sizeof(To) == sizeof(From)` and both must be trivially copyable types.
- When the compiler provides `__builtin_bit_cast`, the call can be used in constant expressions; otherwise it is implemented via a `memcpy` fallback, in which case `To` must be default constructible.

## Example

The following snippet shows the call on this page with concrete values.

```cpp
#include <asc/std/bit>

decltype(auto) example()
{
    return asc::std::bit_cast<unsigned int>(1.0f);
}
```

## Related APIs

- [API list for this header](asc_std_bit.md)
