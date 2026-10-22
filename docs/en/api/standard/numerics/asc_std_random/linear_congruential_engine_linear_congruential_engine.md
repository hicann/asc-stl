# asc::std::linear_congruential_engine::linear_congruential_engine

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

`asc::std::linear_congruential_engine::linear_congruential_engine` initializes a `linear_congruential_engine` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

### Prototype 1

```cpp
constexpr linear_congruential_engine() noexcept;
```

### Prototype 2

```cpp
explicit constexpr linear_congruential_engine(result_type seed) noexcept;
```

### Prototype 3

```cpp
template<class Sseq, enable_if_t<detail::__is_seed_sequence<Sseq, linear_congruential_engine>::value, int> = 0>
explicit constexpr linear_congruential_engine(Sseq& sequence) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `seed` | Input | Seed value used to initialize or reset the state of the pseudorandom number engine. |

### Parameters of Prototype 3

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

- The seed object yields one integer through a no-argument call; when the modulus is non-zero, the integer is reduced modulo it and normalized according to the increment and zero-state rules. This form does not accept a standard SeedSequence that only has a generate member.

- Provides the standard seed, discard, generation, and equality comparison members that do not accept a seed_seq.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    using Engine = asc::std::minstd_rand;
    Engine engine(1);
    return engine() == 48271;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
