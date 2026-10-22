# asc::std::linalg::scaled_accessor::scaled_accessor

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

`asc::std::linalg::scaled_accessor::scaled_accessor` initializes a `scaled_accessor` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

### Prototype 1

```cpp
constexpr scaled_accessor();
```

### Prototype 2

```cpp
constexpr scaled_accessor(const ScalingFactor& scale, const NestedAccessor& accessor);
```

### Prototype 3: Converting Construction

```cpp
template <class OtherScalingFactor, class OtherNestedAccessor,
    enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
            is_constructible_v<ScalingFactor, OtherScalingFactor> &&
            !is_convertible_v<OtherNestedAccessor, NestedAccessor>,
        int> = 0>
explicit constexpr scaled_accessor(
    const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other);
```

```cpp
template <class OtherScalingFactor, class OtherNestedAccessor,
    enable_if_t<is_constructible_v<NestedAccessor, const OtherNestedAccessor&> &&
            is_constructible_v<ScalingFactor, OtherScalingFactor> &&
            is_convertible_v<OtherNestedAccessor, NestedAccessor>,
        int> = 0>
constexpr scaled_accessor(const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `scale` | Input | Reference to the object used by "initializes a `scaled_accessor` object with the constructor forms listed on this page"; the referenced object must remain valid during the call. |
| `accessor` | Input | Reference to the object used by "initializes a `scaled_accessor` object with the constructor forms listed on this page"; the referenced object must remain valid during the call. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `OtherScalingFactor` | Type of the source scaling factor; must be able to construct the current scaling factor. |
| `OtherNestedAccessor` | Source accessor type; must be convertible to the current nested accessor type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | Source object of the construction; this object is initialized from its corresponding members or underlying state, and the rvalue form may move that state. |

## Return Value

No return value.

## Constraints

- The converting constructor participates only when the nested accessor is constructible from a const source; scaled_accessor additionally requires the scaling factor to be constructible. When the nested accessor is implicitly convertible, the constructor is not explicit; otherwise it must be constructed explicitly.

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
