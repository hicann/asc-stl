# asc::pcg64_engine::discard

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

`asc::pcg64_engine::discard` advances the engine state and discards the specified number of pseudorandom results.

## Function Prototype

Member of: [`asc::pcg64_engine`](pcg64_engine.md).

```cpp
// Excerpt of the declaration inside the asc::pcg64_engine class; template parameters and other members are provided by the enclosing class.
constexpr void discard(unsigned long long count) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `count` | Input | Number of elements participating in the operation. |

## Return Value

No return value.

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host snippet demonstrates the call with concrete values; inputs must satisfy the constraints on this page.

```cpp
#include <asc/random>

void example()
{
    asc::pcg64 generator{};
    generator.discard(4);
}
```

## Related APIs

- [`asc::pcg64_engine`](pcg64_engine.md)
- [API list for this header](asc_random.md)
