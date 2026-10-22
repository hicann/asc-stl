# asc::std::linalg::scaled_accessor::reference

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

`asc::std::linalg::scaled_accessor::reference` identifies the return type of the element computation result; in the instance on this page it is returned by value, and writing back to the underlying elements is not supported.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Declaration

Member of: [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::scaled_accessor class; template parameters and other members are provided by the enclosing class.
using reference = remove_const_t<element_type>;
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
    static_assert(asc::std::is_same_v<Accessor::reference, float>);
    return true;
}
```

## Related APIs

- [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)
- [API list for this header](asc_std_linalg.md)
