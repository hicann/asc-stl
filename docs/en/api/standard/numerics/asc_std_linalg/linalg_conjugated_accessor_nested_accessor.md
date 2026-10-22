# asc::std::linalg::conjugated_accessor::nested_accessor

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

`asc::std::linalg::conjugated_accessor::nested_accessor` returns the accessor stored inside the composing accessor.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

Member of: [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::conjugated_accessor class; template parameters and other members are provided by the enclosing class.
constexpr const NestedAccessor& nested_accessor() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `const NestedAccessor &` | Returns the accessor stored inside the composing accessor. |

## Constraints

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the results while the object and the underlying storage are still valid.

```cpp
#include <asc/std/linalg>
#include <asc/std/type_traits>

bool example()
{
    using N = asc::std::default_accessor<asc::std::complex<float>>;
    asc::std::linalg::conjugated_accessor<N> accessor{};
    const N& nested = accessor.nested_accessor();
    static_assert(asc::std::is_same_v<decltype(accessor.nested_accessor()), const N&>);
    return &nested == &accessor.nested_accessor();
}
```

## Related APIs

- [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)
- [API list for this header](asc_std_linalg.md)
