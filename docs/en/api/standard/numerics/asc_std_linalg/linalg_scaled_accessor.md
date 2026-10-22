# asc::std::linalg::scaled_accessor

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

Header: `<asc/std/linalg>`.

`asc::std::linalg::scaled_accessor` defines an access policy that computes the result by value on reads; it does not write back to the underlying elements through the return value.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Declaration

```cpp
namespace asc::std::linalg {
template<class ScalingFactor, class NestedAccessor> class scaled_accessor;
} // namespace asc::std::linalg
```

## Constraints

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>
#include <asc/std/type_traits>

using Accessor = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;

bool example()
{
    float values[] = {3.0f};
    Accessor accessor(2.0f, asc::std::default_accessor<float>{});
    auto value = accessor.access(values, 0);
    return value == 6.0f;
}
```

## Related APIs

- [API list for this header](asc_std_linalg.md)
