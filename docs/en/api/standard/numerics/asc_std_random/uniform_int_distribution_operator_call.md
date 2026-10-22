# asc::std::uniform_int_distribution::`operator()`

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

`asc::std::uniform_int_distribution::operator()` processes the current object and operands according to the operator rules available for `uniform_int_distribution`.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

Member of: [`asc::std::uniform_int_distribution`](uniform_int_distribution.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::std::uniform_int_distribution class; template parameters and other members are provided by the enclosing class.
template<class URng> constexpr result_type operator()(URng& generator) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::std::uniform_int_distribution class; template parameters and other members are provided by the enclosing class.
template<class URng> constexpr result_type operator()(URng& generator, const param_type& parameters) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `URng` | Unsigned uniform random bit generator providing result_type, min(), max(), and a no-argument call. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `generator` | Input/Output | Produces random bits; the call advances its state. |
| `parameters` | Input | Distribution interval parameters used by Prototype 2, overriding the parameters used for this sampling; the parameters saved in the distribution object are not changed. |

Prototype 1 uses the parameters currently saved in the object.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `result_type` | Returns the next random value produced after advancing the random number engine. |
| Prototype 2 | `result_type` | Returns the next random value produced after advancing the random number engine. |

## Constraints

- All standard integer result types are supported.

## Example

The following Host snippet demonstrates the call with concrete types; the input ranges and objects must remain valid for the duration of use.

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
    asc::std::uniform_int_distribution<int> distribution(0, 9);
    return distribution(generator);
}
```

## Related APIs

- [`asc::std::uniform_int_distribution`](uniform_int_distribution.md)
- [API list for this header](asc_std_random.md)
