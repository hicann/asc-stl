# asc::std::uniform_real_distribution::uniform_real_distribution

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

Constructs a float uniform real distribution, and sets or keeps the default half-open sampling interval.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

### Prototype 1

```cpp
constexpr asc::std::uniform_real_distribution<float>::uniform_real_distribution() noexcept;
```

### Prototype 2

```cpp
constexpr explicit asc::std::uniform_real_distribution<float>::uniform_real_distribution(const param_type& parameters) noexcept;
```

### Prototype 3

```cpp
constexpr explicit asc::std::uniform_real_distribution<float>::uniform_real_distribution(float a, float b = 1.0F) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `parameters` | Input | Reference to a distribution parameter object; initializes this distribution with its saved half-open sampling interval. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Lower bound of the half-open sampling interval; generated values satisfy a <= x < b. |
| `b` | Input | Upper bound of the half-open sampling interval; 1.0F when omitted (see the default argument of Prototype 3). |

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
    asc::std::uniform_real_distribution<float> distribution(2.0f, 5.0f);
    asc::std::minstd_rand engine(7);
    const auto value = distribution(engine);
    return value >= 2.0f && value < 5.0f;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
