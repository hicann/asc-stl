# asc::std::uniform_real_distribution::param_type::param_type

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

Header: `<asc/std/random>`.

Constructs a half-open interval parameter object for the float uniform real distribution.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

```cpp
constexpr explicit asc::std::uniform_real_distribution<float>::param_type::param_type(float a = 0.0F, float b = 1.0F) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Lower bound of the half-open interval of the uniform real distribution; generated values satisfy a <= x < b, and it is 0.0F when omitted. |
| `b` | Input | Upper bound of the half-open interval of the uniform real distribution; 1.0F when omitted. |

## Return Value

No return value.

## Constraints

- Only uniform_real_distribution<float> is provided.
- Results lie within the specified half-open interval; no double, long double, or other statistical distributions are provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    asc::std::uniform_real_distribution<float>::param_type parameters(2.0f, 5.0f);
    return parameters.a() == 2.0f && parameters.b() == 5.0f;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
