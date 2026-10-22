# asc::tensor_copy_descriptor

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

`asc::tensor_copy_descriptor` describes the extents, source/destination strides, and both-side paddings of a multidimensional tensor transfer.

## Declaration

```cpp
namespace asc {
template<unsigned Rank> class tensor_copy_descriptor;
} // namespace asc
```

## Constraints

- `Rank` must be a compile-time unsigned integer from 1 to 5; dimensions are numbered from outermost to innermost, with the innermost dimension being `Rank - 1`.
- Extents, source/destination strides, and left/right paddings are stored as 32-bit unsigned element counts; the descriptor owns these values and does not own or reference the source/destination data storage.
- Construction and queries can be done in Host, AI Core SIMD programming, and AI Core SIMT programming; they do not start any data transfer. Before an actual transfer, [validate](tensor_copy_descriptor_validate.md) must be called and the storage, address space, and synchronization requirements of the transfer interface must be satisfied.

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
