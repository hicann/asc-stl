# `asc::std::operator<<=`

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

`asc::std::operator<<=` shifts the integer value of the std::byte contained in `lhs` left by `shift` bits, stores the shift result back into `lhs`, and returns a reference to it. `shift` must be a non-negative integer, and the shift count must be less than the width in bits of `unsigned int`; the operation first promotes the byte value to `unsigned int`, and converts it back to `byte` after the shift.

Standard semantics reference: [cppreference `cstddef`](https://en.cppreference.com/w/cpp/header/cstddef).

## Function Prototype

```cpp
namespace asc::std {
template<class Integer> constexpr byte& operator<<=(byte& lhs, Integer shift) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Integer` | The integer type of the shift count. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input/Output | The byte object updated by the left shift; shifted left by shift bits according to its underlying unsigned char, and a reference to it is returned. |
| `shift` | Input | The number of bits to shift left. |

## Return Value

| Return type | Description |
| --- | --- |
| `byte &` | Returns a reference to `lhs` after the left shift result is stored back, which can continue to be used in assignment or compound operations. |

## Constraints

- The standard declaration is provided.

## Example

The following Host example uses concrete inputs and checks an observable result of the interface.

```cpp
#include <asc/std/cstddef>

bool example()
{
    asc::std::byte value{3};
    auto& result = (value <<= 1);
    return &result == &value && asc::std::to_integer<unsigned>(value) == 6;
}
```

## Related APIs

- [API list for this header](asc_std_cstddef.md)
