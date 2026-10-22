# asc::std::layout_stride::mapping::strides

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

Header: `<asc/std/mdspan>`.

`asc::std::layout_stride::mapping::strides` returns the array of per-dimension strides.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

```cpp
asc::std::array<typename asc::std::layout_stride::mapping<Extents>::index_type, Extents::rank()> asc::std::layout_stride::mapping<Extents>::strides() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `As declared` | A copy of the array holding the stride of each dimension in dimension order. |

## Constraints

- The stride array is consistent with the number of dimensions and never throws.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.strides(static_cast<Args&&>(args)...);
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
