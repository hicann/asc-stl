# `asc::operator!=` (Function template)

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

`asc::operator!=` compares whether the current states of two PCG64 engines with the same parameters differ.

## Function Prototype

```cpp
template<asc::std::uint64_t AHigh, asc::std::uint64_t ALow, asc::std::uint64_t CHigh, asc::std::uint64_t CLow> constexpr bool asc::operator!=(const asc::pcg64_engine<AHigh, ALow, CHigh, CLow>& left, const asc::pcg64_engine<AHigh, ALow, CHigh, CLow>& right) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `AHigh` | High 64 bits of the PCG64 state transition multiplier A, a compile-time unsigned integer constant. |
| `ALow` | Low 64 bits of the PCG64 state transition multiplier A, a compile-time unsigned integer constant. |
| `CHigh` | High 64 bits of the PCG64 state transition increment C, a compile-time unsigned integer constant. |
| `CLow` | Low 64 bits of the PCG64 state transition increment C, a compile-time unsigned integer constant. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left PCG64 engine in the inequality comparison; its current state is compared. |
| `right` | Input | Right PCG64 engine in the inequality comparison; its current state is compared. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- The random number engine supports only the unsigned integer state, seed, and counter forms declared on this page.
- No SeedSequence, streaming input/output, or shared global state is provided.

## Example

The following snippet provides concrete template arguments and call objects.

```cpp
#include <asc/random>

decltype(auto) example()
{
    asc::pcg64 left;
    asc::pcg64 right;
    return asc::operator!=(left, right);
}
```

## Related APIs

- [API list for this header](asc_random.md)
