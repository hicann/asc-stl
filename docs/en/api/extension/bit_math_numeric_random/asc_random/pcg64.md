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

A fixed PCG XSL-RR 128/64 oneseq engine.

## Declaration

```cpp
namespace asc {
class pcg64 {
public:
    using result_type = asc::std::uint64_t;
    static constexpr result_type default_seed = 0xcafef00dd15ea5e5ULL;
    constexpr pcg64() noexcept;
    constexpr explicit pcg64(result_type seed) noexcept;
    constexpr pcg64(const pcg64&) noexcept = default;
    constexpr pcg64& operator=(const pcg64&) noexcept = default;
    constexpr void seed(result_type seed = default_seed) noexcept;
    constexpr result_type operator()() noexcept;
    constexpr void discard(unsigned long long count) noexcept;
    static constexpr result_type min() noexcept;
    static constexpr result_type max() noexcept;
};
constexpr bool operator==(const pcg64&, const pcg64&) noexcept;
constexpr bool operator!=(const pcg64&, const pcg64&) noexcept;
} // namespace asc
```

## Constraints

Available in C++17/C++20 on Host and Ascend 950 SIMT / ordinary SIMD scalar code. All operations are constexpr and noexcept.

State arithmetic is modulo `2^128`:

```text
A = 2549297995355413924 * 2^64 + 4865540595714422341
C = 6364136223846793005 * 2^64 + 1442695040888963407
T(S) = A*S + C (mod 2^128)
seed(z): S = T(C + zero_extend_128(z))
operator(): S = T(S); result = rotr64((S >> 64) xor low64(S), S >> 122)
```

The rotation is 0..63; zero preserves the value. A is 1 modulo 4 and C is odd, giving a `2^128` state period. Every 64-bit seed is valid. Seeding emits no output. Default construction, an explicit default_seed and seed() establish the same state.

Copying and assignment preserve every state bit. Equality compares all state bits; one equal output is insufficient. discard(0) preserves state. discard(n) is equivalent to n raw calls, using affine exponentiation in `O(log(n+1))` time for `0..ULLONG_MAX`. Callers must keep offset arithmetic representable.

The same seed and raw position reproduce the same integers on supported Host/Device paths. Object bytes, raw memory serialization and ABI are not a cross-backend contract. Distribution results have no bitwise guarantee across libraries, versions or backends.

This type meets the uniform random bit generator requirements. Include `<asc/std/random>` explicitly to use supported integer distributions, `uniform_real_distribution<float>` or `generate_canonical<float, Bits>`. SeedSequence and stream I/O are not provided; complete standard random engine requirements are not promised.

Give each logical task a private engine. With a shared seed, a stable task ID `t < 2^32` may reserve 1024 raw calls, discard(t*1024ULL), then consume at most 1024 calls. Start offsets are below `2^42`, so positions do not overlap. Stable IDs and per-task call histories preserve results across scheduling changes. Different positions may return equal values. Different seeds or segments do not establish statistical independence. Distribution sampling may consume a variable number of raw calls.

For non-cryptographic use. XSL-RR has known correlations among very large collections of long parallel sequences, especially with shared low state bits. The algorithm follows the author's [pcg64_oneseq reference](https://github.com/imneme/pcg-cpp/blob/428802d1a5634f96bcd0705fab379ff0113bcf13/include/pcg_random.hpp); see [NumPy's parallel-use analysis](https://numpy.org/doc/stable/reference/random/upgrading-pcg64.html).

## Example

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(42);
    return engine() == 0x287472e87ff5705aULL;
}
```

## Related APIs

- [Header API list](asc_random.md)
