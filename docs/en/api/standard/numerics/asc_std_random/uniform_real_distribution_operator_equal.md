# `asc::std::operator==` (uniform_real_distribution)

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

Compares the distribution parameters; equivalent to comparing the lower and upper bounds.

## Function Prototype

The following is a friend function declaration in the `asc::std` namespace; execution-space macros are omitted.

```cpp
// Inside the body of the uniform_real_distribution class template; the class name of the current instantiation is the injected-class-name.
friend constexpr bool operator==(const uniform_real_distribution& left, const uniform_real_distribution& right) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The left operand of the comparison; the comparison does not modify it. |
| `right` | Input | The right operand of the comparison; the comparison does not modify it. |

## Return Value

Returns `bool`: `true` when the comparison relation holds, otherwise `false`.

## Constraints

- This is a non-template friend defined inside the class; it participates in comparison through argument-dependent lookup (ADL).
- The comparison does not advance the engine and does not generate random numbers.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::uniform_real_distribution<float> left, right;
    return left == right;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
