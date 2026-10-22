# asc::pcg64_engine::default_seed

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

`asc::pcg64_engine::default_seed` defines the default 64-bit seed of the PCG64 engine.

## Declaration

Member of: [`asc::pcg64_engine`](pcg64_engine.md).

```cpp
// Excerpt of the declaration inside the asc::pcg64_engine class; template parameters and other members are provided by the enclosing class.
static constexpr asc::std::uint64_t default_seed = 0xcafef00dd15ea5e5ULL;
```

## Constraints

- The type, alias, or field on this page only describes the stored random state or permutation information; observing it invokes no runtime and accesses no shared global state.
- Mapping calls must use a non-empty finite domain and in-domain indices; for the seed and counter requirements of generator calls, see their member pages.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/random>
#include <asc/std/limits>

bool example()
{
    static_assert(asc::pcg64::default_seed == 0xcafef00dd15ea5e5ULL);
    asc::pcg64 engine(7);
    const auto first = engine();
    engine.seed(7);
    return engine() == first;
}
```

## Related APIs

- [`asc::pcg64_engine`](pcg64_engine.md)
- [API list for this header](asc_random.md)
