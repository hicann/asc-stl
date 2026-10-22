# asc::std::linalg::scaled_accessor::access

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

`asc::std::linalg::scaled_accessor::access` reads the element at the given index and returns the scaling result by value, without modifying the original element.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

Member of: [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::linalg::scaled_accessor class; template parameters and other members are provided by the enclosing class.
constexpr reference access(data_handle_type pointer, size_t index) const;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Underlying data handle, pointing to the storage of the element to be accessed. |
| `index` | Input | Element index of the element to be accessed, relative to the handle's origin. |

## Return Value

In the example on this page, `reference` is actually `float`; the scaling result is returned by value and is not a reference to the original array element.

| Return type | Description |
| --- | --- |
| `reference` | Returns the result of the scaling computation; the concrete return type is determined by `reference`, and whether it is a C++ reference cannot be judged from this alias alone. |

## Constraints

- The data handle must allow the nested accessor to access that index; the underlying storage must remain valid during the call.
- The element type and the scaling factor must support the corresponding multiplication expression.

## Example

The following Host example verifies the scaling result and that the original data is unchanged.

```cpp
#include <asc/std/linalg>

bool example()
{
    float values[2] = {2.0F, 4.0F};
    using accessor_type = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;
    accessor_type accessor(3.0F, asc::std::default_accessor<float>{});
    return accessor.access(values, 1) == 12.0F && values[1] == 4.0F;
}
```

## Related APIs

- [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)
- [API list for this header](asc_std_linalg.md)
