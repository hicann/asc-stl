# asc::tensor_copy_descriptor::size_type

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

Header: `<asc/tensor_copy>`.

`asc::tensor_copy_descriptor::size_type` is the numeric type for the dimensions and strides of the tensor copy descriptor.

## Declaration

`size_type` is a member type alias of the class template `asc::tensor_copy_descriptor<Rank>`, declared in the class template context as follows:

```cpp
template<unsigned Rank>
class asc::tensor_copy_descriptor {
public:
    using size_type = unsigned int;
};
```

## Constraints

In generic code, size variables can be declared through `size_type` of the enclosing type without hard-coding the underlying integer type; see the enclosing type page for the relationship between this alias and the other member types.

- This alias denotes the unsigned integer type used by the enclosing type for element counts or sizes; reading the type itself allocates no memory and accesses no elements.
- For the run-time conditions of construction, assignment, and access, see the enclosing type [asc::tensor_copy_descriptor](tensor_copy_descriptor.md).

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/tensor_copy>
#include <asc/std/type_traits>

bool example()
{
    using Descriptor = asc::tensor_copy_descriptor<2>;
    static_assert(asc::std::is_same_v<Descriptor::size_type, unsigned int>);
    Descriptor descriptor;
    return descriptor.rank() == 2 && descriptor.validate() == asc::tensor_copy_status::zero_extent;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
