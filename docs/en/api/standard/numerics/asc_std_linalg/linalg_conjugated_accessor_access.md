# asc::std::linalg::conjugated_accessor::access

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

`asc::std::linalg::conjugated_accessor::access` reads the element at the given index and returns the conjugation result by value, without modifying the original element.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

Member of: [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::conjugated_accessor class; template parameters and other members are provided by the enclosing class.
constexpr reference access(data_handle_type pointer, size_t index) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Underlying data handle, pointing to the storage of the element to be accessed. |
| `index` | Input | Element index of the element to be accessed, relative to the handle's origin. |

## Return Value

In the example on this page, `reference` is actually `asc::std::complex<float>`; the conjugation result is returned by value and is not a reference to the original array element.

| Return type | Description |
| --- | --- |
| `reference` | Returns the result of the conjugation computation; the concrete return type is determined by `reference`, and whether it is a C++ reference cannot be judged from this alias alone. |

## Constraints

- The data handle must allow the nested accessor to access that index; the underlying storage must remain valid during the call.
- The element type and the conjugation operation must satisfy the requirements of the nested accessor and the conjugation function.

## Example

The following Host example verifies the conjugation result and that the original data is unchanged.

```cpp
#include <asc/std/linalg>

bool example()
{
    asc::std::complex<float> values[1] = {{2.0F, 3.0F}};
    using accessor_type = asc::std::linalg::conjugated_accessor<asc::std::default_accessor<asc::std::complex<float>>>;
    accessor_type accessor{};
    const auto result = accessor.access(values, 0);
    return result.real() == 2.0F && result.imag() == -3.0F && values[0].imag() == 3.0F;
}
```

## Related APIs

- [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)
- [API list for this header](asc_std_linalg.md)
