# asc::std::linear_congruential_engine::`operator()`

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

`asc::std::linear_congruential_engine::operator()` processes the current object and operands according to the operator rules available for `linear_congruential_engine`.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

Member of: [`asc::std::linear_congruential_engine`](linear_congruential_engine.md).

```cpp
// Excerpt of the declaration inside the asc::std::linear_congruential_engine class; template parameters and other members are provided by the enclosing class.
constexpr result_type operator()() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `result_type` | Returns the next random value produced after advancing the random number engine. |

## Constraints

- Provides the standard seed, discard, generation, and equality comparison members that do not accept a seed_seq.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and parameters must satisfy the constraints on this page.

```cpp
#include <asc/std/random>

decltype(auto) example()
{
    asc::std::minstd_rand generator{};
    return generator();
}
```

## Related APIs

- [`asc::std::linear_congruential_engine`](linear_congruential_engine.md)
- [API list for this header](asc_std_random.md)
