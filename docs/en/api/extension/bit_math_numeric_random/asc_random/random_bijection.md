# asc::random_bijection

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

`asc::random_bijection` constructs a one-to-one mapping over a finite index domain, determined by a random seed.

## Declaration

```cpp
namespace asc {
// Declaration summary: default template arguments are described below.
template <class Index, class Bijection>
class random_bijection;
}  // namespace asc
```

`Index` defaults to a 64-bit unsigned integer type. `Bijection` defaults to the permutation implementation provided by the library, so the caller can construct `asc::random_bijection<>` directly without naming the default implementation type. A custom `Bijection` must support construction from a range size and a random number generator and invocation with an `Index` value; repeated invocations within its permutation domain must be able to return to `[0, size)`.

## Constraints

- When constructing the permutation, the round key is extracted from the high 32 bits of each generator result; a generator whose entropy comes only from the low 32 bits yields all-zero round keys. When random round keys are required, a 64-bit generator whose high bits also carry entropy should be provided.

- The type, alias, or field on this page only describes the stored random state or permutation information; observing it invokes no runtime and accesses no shared global state.
- Mapping calls must use a non-empty finite domain and in-domain indices; for the seed and counter requirements of generator calls, see their member pages.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 generator(7);
    asc::random_bijection<unsigned long long> permutation(4, generator);
    bool seen[4] = {};
    for (unsigned long long i = 0; i < 4; ++i) {
        const auto value = permutation(i);
        if (value >= 4 || seen[value])
            return false;
        seen[value] = true;
    }
    return seen[0] && seen[1] && seen[2] && seen[3];
}
```

## Related APIs

- [API list for this header](asc_random.md)
