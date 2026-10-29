# asc::pcg64_engine::`operator()`

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

`asc::pcg64_engine::operator()` advances the engine state and generates the next 64-bit pseudorandom number.

## Function Prototype

Member of: [`asc::pcg64_engine`](pcg64_engine.md).

```cpp
// Excerpt of the declaration inside the asc::pcg64_engine class; template parameters and other members are provided by the enclosing class.
constexpr result_type operator()() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `result_type` | Returns the next random value produced after advancing the random engine. |

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host snippet demonstrates the call with concrete values; inputs must satisfy the constraints on this page.

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 generator;
    const asc::pcg64::result_type expected[] = {
        14951315693135216709ULL,
        1541401459199960700ULL,
        3670514919227316241ULL,
        11007308355854268502ULL,
        523514384104871782ULL,
        18368464326245194742ULL
    };
    for (auto value : expected) {
        if (generator() != value) return false;
    }
    return true;
}
```

## Related APIs

- [`asc::pcg64_engine`](pcg64_engine.md)
- [API list for this header](asc_random.md)
