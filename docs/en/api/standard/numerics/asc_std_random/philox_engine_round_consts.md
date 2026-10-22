# asc::std::philox_engine::round_consts

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

`asc::std::philox_engine::round_consts` gives the default seed, recurrence parameters, or round count of the current random number engine.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

The following is a member declaration inside the `philox_engine` class. The initialization function generates an array of length WordCount / 2 whose elements are taken from the odd positions of the Constants parameter pack.

```cpp
static constexpr auto round_consts = make_round_consts();
```

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    using Engine = asc::std::philox4x32;
    static_assert(Engine::round_consts[0] == 2654435769U);
    Engine engine(7);
    const auto first = engine();
    engine.seed(7);
    // Re-seeding with the same seed should reproduce the first value of the sequence.
    return engine() == first;
}
```

## Related APIs

- [`asc::std::philox_engine`](philox_engine.md)
- [API list for this header](asc_std_random.md)
