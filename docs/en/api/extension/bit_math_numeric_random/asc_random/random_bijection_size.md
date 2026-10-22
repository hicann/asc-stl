# asc::random_bijection::size

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

`asc::random_bijection::size` returns the size of the finite index domain covered by the one-to-one mapping.

## Function Prototype

Member of: [`asc::random_bijection`](random_bijection.md).

```cpp
// Excerpt of the declaration inside the asc::random_bijection class; template parameters and other members are provided by the enclosing class.
constexpr Index size() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `Index` | Returns the size of the finite index domain covered by the one-to-one mapping. |

## Constraints

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
