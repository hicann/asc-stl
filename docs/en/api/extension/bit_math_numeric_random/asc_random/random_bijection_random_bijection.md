# asc::random_bijection::random_bijection

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

`asc::random_bijection::random_bijection` initializes an `asc::random_bijection` object with caller-provided parameters.

## Function Prototype

Member of: [`asc::random_bijection`](random_bijection.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::random_bijection class; template parameters and other members are provided by the enclosing class.
constexpr random_bijection() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::random_bijection class; template parameters and other members are provided by the enclosing class.
template <class RNG>
constexpr random_bijection(Index size, RNG&& generator) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `RNG` | Random number engine type used to generate the bijection parameters; it must be able to provide the required unsigned random values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `size` | Input | Size of the object or range. |
| `generator` | Input/Output | Generator providing the random numbers; its state may advance during the call. |

## Return Value

No return value.

## Constraints

- When constructing the permutation, the round key is extracted from the high 32 bits of each generator result; a generator whose entropy comes only from the low 32 bits yields all-zero round keys. When random round keys are required, a 64-bit generator whose high bits also carry entropy should be provided.

- The type, alias, or field on this page only describes the stored random state or permutation information; observing it invokes no runtime and accesses no shared global state.
- Mapping calls must use a non-empty finite domain and in-domain indices; for the seed and counter requirements of generator calls, see their member pages.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(7);
    asc::random_bijection<unsigned long long> permutation(8, engine);
    return permutation.size() == 8 && permutation(0) < 8;
}
```

## Related APIs

- [`asc::random_bijection`](random_bijection.md)
- [API list for this header](asc_random.md)
