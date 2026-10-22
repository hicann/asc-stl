# asc::std::linalg::scaled_accessor::scaling_factor

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

`asc::std::linalg::scaled_accessor::scaling_factor` returns the scaling factor used by the composing view.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

Member of: [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::scaled_accessor class; template parameters and other members are provided by the enclosing class.
constexpr ScalingFactor scaling_factor() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `ScalingFactor` | Returns the scaling factor used by the composing view. |

## Constraints

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with a concrete range or accessor; the underlying storage must remain valid during the call.

```cpp
#include <asc/std/linalg>

decltype(auto) example()
{
    using accessor_type = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;
    accessor_type accessor{};
    return accessor.scaling_factor();
}
```

## Related APIs

- [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)
- [API list for this header](asc_std_linalg.md)
