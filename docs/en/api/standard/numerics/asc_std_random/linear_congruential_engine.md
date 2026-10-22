# asc::std::linear_congruential_engine

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

`asc::std::linear_congruential_engine` holds the state of the linear congruential random number engine and generates values.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

```cpp
namespace asc::std {
template<class UIntType, UIntType A, UIntType C, UIntType M> class linear_congruential_engine;
} // namespace asc::std
```

## Constraints

- UIntType must be an unsigned integer without cv qualification. When M is non-zero, A < M and C < M; the engine's effective value range must contain at least two values.

- Provides the standard seed, discard, generation, and equality comparison members that do not accept a seed_seq.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand engine(1);
    return engine() == 48271U;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
