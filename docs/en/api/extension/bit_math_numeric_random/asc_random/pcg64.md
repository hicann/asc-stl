# asc::pcg64

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

`asc::pcg64` is an alias of pcg64_engine with the product-default multiplier and increment parameters.

## Declaration

```cpp
namespace asc {
using pcg64 = pcg64_engine<2549297995355413924ULL, 4865540595714422341ULL, 6364136223846793005ULL, 1442695040888963407ULL>;
} // namespace asc
```

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/random>
#include <asc/std/limits>

bool example()
{
    asc::pcg64 engine(7);
    const auto first = engine();
    engine.seed(7);
    return engine() == first;
}
```

## Related APIs

- [API list for this header](asc_random.md)
