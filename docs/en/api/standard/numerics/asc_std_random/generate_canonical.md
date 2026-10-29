# asc::std::generate_canonical

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

`asc::std::generate_canonical` generates floating-point random values of the specified precision using the caller-provided random number engine.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

```cpp
namespace asc::std {
template<class RealType, size_t Bits, class URng> constexpr RealType generate_canonical(URng& generator) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RealType` | Numeric type produced by the random number engine or distribution; must meet the integer/floating-point requirements of the current engine or distribution. |
| `Bits` | Requested number of bits of random precision; the actual precision does not exceed the significant digits of float, and multiple calls to generator may be needed. |
| `URng` | Uniform random bit generator type providing a no-argument call, min, and max. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `generator` | Input/Output | Generator providing the random numbers; its state may advance during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `RealType` | Returns a normalized float value in the [0, 1) interval; may consume multiple engine outputs. |

## Constraints

- The random number engine is provided by the caller and must satisfy the URBG requirements.
- The result type is float.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/random>

decltype(auto) example()
{
    asc::std::minstd_rand engine;
    return asc::std::generate_canonical<float, 10>(engine);
}

bool verify_example()
{
    return example() > 0.00002247f && example() < 0.00002249f;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
