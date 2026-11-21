# asc::std::linear_congruential_engine::seed

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

`asc::std::linear_congruential_engine::seed` resets the state of the random number engine with the specified seed.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

Member of: [`asc::std::linear_congruential_engine`](linear_congruential_engine.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::std::linear_congruential_engine class; template parameters and other members are provided by the enclosing class.
constexpr void seed(result_type seed) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::std::linear_congruential_engine class; template parameters and other members are provided by the enclosing class.
template<class Sseq, enable_if_t<detail::__is_seed_sequence<Sseq, linear_congruential_engine>::value, int> = 0>
constexpr void seed(Sseq& sequence) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `seed` | Input | Seed value used to initialize or reset the state of the pseudorandom number engine. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Sseq` | Seed sequence type; must be no-argument callable as sequence() to produce unsigned integers, and does not follow the generate(first, last) protocol of the standard seed_seq. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `sequence` | Input/Output | Seed value used to initialize or reset the state of the pseudorandom number engine. |

## Return Value

No return value.

## Constraints

- Both overloads reduce the seed integer modulo the effective modulus. When `M` is zero, this keeps the low bits representable in `result_type`. If `C` and the remainder are both zero, the initial state is 1. Otherwise the remainder is the initial state.
- A seed object supplies one integer through the call `sequence()`.

- Provides the standard seed, discard, generation, and equality comparison members that do not accept a seed_seq.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and parameters must satisfy the constraints on this page.

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand generator;
    generator.seed(9);
    return generator() == 434439u;
}
```

## Related APIs

- [`asc::std::linear_congruential_engine`](linear_congruential_engine.md)
- [API list for this header](asc_std_random.md)
