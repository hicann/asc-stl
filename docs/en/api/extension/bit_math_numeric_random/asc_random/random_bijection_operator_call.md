# asc::random_bijection::`operator()`

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

`asc::random_bijection::operator()` maps an input index to a unique permutation index within the finite domain.

## Function Prototype

Member of: [`asc::random_bijection`](random_bijection.md).

```cpp
// Excerpt of the declaration inside the asc::random_bijection class; template parameters and other members are provided by the enclosing class.
constexpr Index operator()(Index index) const noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | Index to be mapped, which must belong to [0, size); the result stays within the same finite domain. |

## Return Value

| Return type | Description |
| --- | --- |
| `Index` | Returns the permutation index corresponding to this index; the same object returns the same value for the same index, without advancing the random engine. |

## Constraints

- The type, alias, or field on this page only describes the stored random state or permutation information; observing it invokes no runtime and accesses no shared global state.
- Mapping calls must use a non-empty finite domain and in-domain indices; for the seed and counter requirements of generator calls, see their member pages.

## Example

The following Host snippet demonstrates the call with concrete values; inputs must satisfy the constraints on this page.

```cpp
#include <asc/random>

decltype(auto) example()
{
    asc::pcg64 generator(9);
    asc::random_bijection<unsigned long long> mapping(17, generator);
    return mapping(3);
}
```

## Related APIs

- [`asc::random_bijection`](random_bijection.md)
- [API list for this header](asc_random.md)
