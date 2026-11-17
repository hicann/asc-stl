# asc::std::uniform_real_distribution::`operator()`

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

`asc::std::uniform_real_distribution::operator()` processes the current object and operands according to the operator rules available for `uniform_real_distribution`.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

### Prototype 1

```cpp
template<class URng> constexpr float asc::std::uniform_real_distribution<float>::operator()(URng& engine) const noexcept;
```

### Prototype 2

```cpp
template<class URng> constexpr float asc::std::uniform_real_distribution<float>::operator()(URng& engine, const param_type& parameters) const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `URng` | Unsigned uniform random bit generator providing result_type, min(), max(), and a no-argument call. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `engine` | Input/Output | Produces random bits; the call advances its state. |
| `parameters` | Input | Distribution interval parameters used by Prototype 2, overriding the parameters used for this sampling; the parameters saved in the distribution object are not changed. |

Prototype 1 uses the parameters currently saved in the object.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `float` | Returns the next random value produced after advancing the random number engine. |
| Prototype 2 | `float` | Returns the next random value produced after advancing the random number engine. |

## Constraints

- Only uniform_real_distribution<float> is provided.
- Results lie within the specified half-open interval; no double, long double, or other statistical distributions are provided.

## Example

If floating-point rounding makes the affine result equal to the upper endpoint,
the implementation returns its representable predecessor, bounded below by the
lower endpoint. This correction uses ASC-STL `bit_cast`: Host compilers without
`__builtin_bit_cast` retain the runtime fallback, but calls requiring the
correction cannot be constant-evaluated in that configuration.

With `philox4x32` and the default `[0,1)` distribution, each sample consumes one
32-bit engine output. Tensor partitions must retain the seed and global output
offset rather than restart from the same seed for each tile. Check consumption
separately when using another engine or distribution.

The following Host snippet demonstrates the call with concrete types; pointers, ranges, and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/random>

struct example_generator {
    using result_type = unsigned int;
    unsigned int state = 1;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 2147483647u; }
    result_type operator()() { state = (state * 48271u) % 2147483647u; return state; }
};

decltype(auto) example()
{
    example_generator generator{};
    asc::std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    return distribution(generator);
}

bool verify_example()
{
    const auto result = example();
    return result >= 0.0f && result < 1.0f;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
