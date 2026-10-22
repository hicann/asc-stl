# asc::std::philox_engine::set_counter

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

`asc::std::philox_engine::set_counter` sets the current position of the counter-based random number engine.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Function Prototype

Member of: [`asc::std::philox_engine`](philox_engine.md).

```cpp
// Excerpt of the declaration inside the asc::std::philox_engine class; template parameters and other members are provided by the enclosing class.
constexpr void set_counter(const asc::std::array<UIntType, WordCount>& counter) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `counter` | Input | Full counter word array of length WordCount; passed from the most significant word to the least significant word, each word limited to WordSize bits, and the intra-block output position is reset. |

## Return Value

No return value.

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and parameters must satisfy the constraints on this page.

```cpp
#include <asc/std/random>

void example()
{
    asc::std::philox4x32 generator{};
    asc::std::array<asc::std::philox4x32::result_type, 4> counter{};
    generator.set_counter(counter);
}
```

## Related APIs

- [`asc::std::philox_engine`](philox_engine.md)
- [API list for this header](asc_std_random.md)
