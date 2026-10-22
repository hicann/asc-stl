# asc::std::uniform_real_distribution::result_type

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

`result_type` is the float result type of the uniform real distribution in this release.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

The following is inside the `uniform_real_distribution<float>` class.

```cpp
using result_type = float;
```

## Constraints

- Only uniform_real_distribution<float> is provided.
- Results lie within the specified half-open interval; no double, long double, or other statistical distributions are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/random>

void example()
{
    using result = asc::std::uniform_real_distribution<float>::result_type;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
