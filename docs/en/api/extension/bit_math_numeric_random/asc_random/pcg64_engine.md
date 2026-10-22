# asc::pcg64_engine

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

Header: `<asc/random>`.

`asc::pcg64_engine` implements a deterministic 64-bit PCG pseudorandom number engine that can be seeded and can skip output.

## Declaration

```cpp
namespace asc {
template<asc::std::uint64_t AHigh, asc::std::uint64_t ALow, asc::std::uint64_t CHigh, asc::std::uint64_t CLow> class pcg64_engine;
} // namespace asc
```

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 first(7);
    asc::pcg64 second(7);
    return first() == second() && first() == second();
}
```

## Related APIs

- [API list for this header](asc_random.md)
