# asc::std::philox4x64

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

`asc::std::philox4x64` provides a type alias for the corresponding random number engine or distribution parameters.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

```cpp
namespace asc::std {
using philox4x64 = philox_engine<uint_fast64_t, 64, 4, 10, 14581110107779764567UL, 11400714819323198485UL, 15197193596820024467UL, 13503953896175478587UL>;
} // namespace asc::std
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
    using Engine = asc::std::philox4x64;
    Engine engine(7);
    const auto first = engine();
    engine.seed(7);
    // Re-seeding with the same seed should reproduce the first value of the sequence.
    return engine() == first;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
