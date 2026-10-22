# asc::std::linalg::scaled_accessor::offset

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

`asc::std::linalg::scaled_accessor::offset` moves the underlying data handle according to the mapping result.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

Member of: [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::scaled_accessor class; template parameters and other members are provided by the enclosing class.
constexpr typename offset_policy::data_handle_type offset(data_handle_type pointer, size_t index) const;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Underlying data handle to be moved. |
| `index` | Input | Number of elements by which the handle moves forward. |

## Return Value

| Return type | Description |
| --- | --- |
| `typename offset_policy::data_handle_type` | Returns the data handle advanced by index elements via the nested accessor; the default accessor returns a pointer within the same underlying array, and the storage must remain valid while the handle is in use. |

## Constraints

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the results while the object and the underlying storage are still valid.

```cpp
#include <asc/std/linalg>

bool example()
{
    float values[2]{};
    using A = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;
    A accessor{};
    const auto pointer = accessor.offset(values, 1);
    return pointer == values + 1;
}
```

## Related APIs

- [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)
- [API list for this header](asc_std_linalg.md)
