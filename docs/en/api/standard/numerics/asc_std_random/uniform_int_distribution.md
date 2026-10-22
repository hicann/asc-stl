# asc::std::uniform_int_distribution

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

`asc::std::uniform_int_distribution` maps results of a random number engine to values within a given integer interval.

Standard semantics reference: [cppreference `random`](https://en.cppreference.com/w/cpp/header/random).

## Declaration

```cpp
namespace asc::std {
template<class IntType = int> class uniform_int_distribution;
} // namespace asc::std
```

## Constraints

- All standard integer result types are supported.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/random>

bool example()
{
    asc::std::minstd_rand engine(1);
    asc::std::uniform_int_distribution<int> distribution(2, 4);
    const int value = distribution(engine);
    return distribution.a() == 2 && distribution.b() == 4 && value >= 2 && value <= 4;
}
```

## Related APIs

- [API list for this header](asc_std_random.md)
