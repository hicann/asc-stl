# asc::std::uniform_int_distribution::reset

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

`asc::std::uniform_int_distribution::reset` clears the currently saved values or state.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

Member of: [`asc::std::uniform_int_distribution`](uniform_int_distribution.md).

```cpp
// Excerpt of the declaration inside the asc::std::uniform_int_distribution class; template parameters and other members are provided by the enclosing class.
constexpr void reset() noexcept;
```

## Parameters

No parameters.

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
    distribution.reset();
    asc::std::minstd_rand engine(7);
    const auto value = distribution(engine);
    return value >= 2 && value <= 5;
}
```

## Related APIs

- [`asc::std::uniform_int_distribution`](uniform_int_distribution.md)
- [API list for this header](asc_std_random.md)
