# asc::pcg64::seed

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

Restart at the first result for the seed; zero and the maximum seed are valid.

## Declaration

Member of [`asc::pcg64`](pcg64.md); the declaration is in class context.

```cpp
constexpr void seed(result_type seed = default_seed) noexcept;
```

## Constraints

Available in C++17/C++20 on Host and Ascend 950 SIMT / ordinary SIMD scalar code. All operations are constexpr and noexcept.

See [pcg64](pcg64.md) for the algorithm, seed mapping, comparison and advancement rules.

## Example

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(42);
    const auto before = engine();
    engine.seed(0);
    const auto zero = engine();
    engine.seed(18446744073709551615ULL);
    return before == 0x287472e87ff5705aULL && zero == 0x01070196e695f8f1ULL && engine() == 0x3b17d015242767f3ULL;
}
```

## Related APIs

- [Header API list](asc_random.md)
