# asc::to_host_mdspan

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

Header: `<asc/mdspan>`.

`asc::to_host_mdspan` creates a host_mdspan from a Host data pointer, extents, and strides.

## Function Prototype

```cpp
namespace asc {
template <class Element, asc::std::size_t Rank, class Layout = asc::layout_stride_relaxed>
bool to_host_mdspan(const DLTensor& tensor,
    asc::host_mdspan<Element, asc::std::dextents<asc::std::size_t, Rank>, Layout>& output) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Element` | The type of the elements accessed by the view; the underlying storage must contain the corresponding valid objects. |
| `Rank` | A type or compile-time value representing the element count, dimension, bit width, or index, as determined by the declaration. |
| `Layout` | The dimension, index mapping, layout, or access policy type used by the multidimensional view. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `tensor` | Input | The tensor description to convert or transfer; its data pointer, shape, and strides must be valid. |
| `output` | Output | Provides a non-owning multidimensional data view; the underlying storage must remain valid while the view is in use. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- The DLPack bridge is provided only when the real `<dlpack/dlpack.h>` can be included, and it is called only on the Host; the conversion neither allocates nor takes over data.

- Host import accepts only kDLCPU, and GM import accepts only kDLExtDev; ndim must equal Rank, and a non-zero Rank requires shape.
- The corresponding DLPack dtypes of float/double and standard signed and unsigned integers are supported; code, bits, and lanes must match (lanes is 1), and unsupported combinations return false.
- data must be non-null, every dimension of shape must be non-negative, byte_offset must satisfy the natural alignment of the element, and the offsets and signed spans must be representable; any failed check leaves output unchanged.
- The conversion only borrows the original data; after success, the valid underlying storage must cover the view accesses. Negative strides require the original tensor data to point to the correct logical origin.

- The default and Host/GM/UB accessors use non-negative element offsets; when negative strides are used manually, the mapping origin must guarantee that the offsets of all valid coordinates are non-negative and still within the storage.
- DLPack import preserves signed strides and expresses reversed views by relocating the handle and setting a non-negative origin; stride spans that cannot be represented return false and leave the output unchanged.


## Example

The DLPack bridge interface is available only when the DLPack headers are provided; the following Host snippet borrows view and tensor storage managed by the caller.

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

#if __has_include(<dlpack/dlpack.h>)
decltype(auto) example(const DLTensor& tensor,
    asc::host_mdspan<int, asc::std::dextents<asc::std::size_t, 2>, asc::layout_stride_relaxed>& output)
{
    return asc::to_host_mdspan<int, 2>(tensor, output);
}
#endif
```

## Related APIs

- [API list for this header](asc_mdspan.md)
