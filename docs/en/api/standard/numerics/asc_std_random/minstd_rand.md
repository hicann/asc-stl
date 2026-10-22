# asc::std::minstd_rand

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

`asc::std::minstd_rand` provides a type alias for the corresponding random number engine or distribution parameters.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

```cpp
namespace asc::std {
using minstd_rand = linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647>;
} // namespace asc::std
```

## Constraints

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
