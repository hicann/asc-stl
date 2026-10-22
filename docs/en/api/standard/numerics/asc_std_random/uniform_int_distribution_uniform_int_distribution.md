# asc::std::uniform_int_distribution::uniform_int_distribution

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

`asc::std::uniform_int_distribution::uniform_int_distribution` initializes a `uniform_int_distribution` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

### Prototype 1

```cpp
constexpr uniform_int_distribution() noexcept;
```

### Prototype 2

```cpp
explicit constexpr uniform_int_distribution(const param_type& parameters) noexcept;
```

### Prototype 3

```cpp
explicit constexpr uniform_int_distribution(result_type minimum, result_type maximum = numeric_limits<result_type>::max()) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `parameters` | Input | Reference to a distribution parameter object; initializes this distribution with its saved closed-interval parameters. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `minimum` | Input | Lower bound of the closed sampling interval; generated values are not less than this value. |
| `maximum` | Input | Upper bound of the closed sampling interval; generated values are not greater than this value. |

## Return Value

No return value.

## Constraints

- All standard integer result types are supported.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    asc::std::uniform_int_distribution<int> distribution(2, 5);
    asc::std::minstd_rand engine(7);
    const auto value = distribution(engine);
    return value >= 2 && value <= 5;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
