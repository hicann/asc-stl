# asc::pcg64_engine::pcg64_engine

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

`asc::pcg64_engine::pcg64_engine` initializes an `asc::pcg64_engine` object with caller-provided parameters.

## Function Prototype

Member of: [`asc::pcg64_engine`](pcg64_engine.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::pcg64_engine class; template parameters and other members are provided by the enclosing class.
constexpr pcg64_engine() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::pcg64_engine class; template parameters and other members are provided by the enclosing class.
constexpr explicit pcg64_engine(result_type seed) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `seed` | Input | Seed value used to initialize or reset the state of the pseudorandom number engine. |

## Return Value

No return value.

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

- [`asc::pcg64_engine`](pcg64_engine.md)
- [API list for this header](asc_random.md)
