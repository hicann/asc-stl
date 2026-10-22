# asc::std::philox_engine

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

`asc::std::philox_engine` holds the state of the counter-based pseudorandom number engine and generates values.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

```cpp
namespace asc::std {
template<class UIntType, size_t WordSize, size_t WordCount, size_t NumRounds, UIntType... Constants> class philox_engine;
} // namespace asc::std
```

## Constraints

- UIntType must be an unsigned integer without cv qualification. WordSize is only 32 or 64, WordCount is only 2 or 4, the number of Constants must equal WordCount, and NumRounds must be greater than 0.

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::philox4x32 first;
    asc::std::philox4x32 second;
    const auto a = first();
    const auto b = second();
    return a == b && first() == second();
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
