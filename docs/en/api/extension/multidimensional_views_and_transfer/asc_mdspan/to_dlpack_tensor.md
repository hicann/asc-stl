# asc::to_dlpack_tensor

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

`asc::to_dlpack_tensor` converts a compatible mdspan view into a DLPack tensor description.

## Function Prototype

```cpp
namespace asc {
template <class Element, class Extents, class Layout, class Accessor>
bool to_dlpack_tensor(const asc::std::mdspan<Element, Extents, Layout, Accessor>& view, DLDeviceType device_type,
    int device_id, asc::dlpack_tensor<Extents::rank()>& output) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Element` | The element type of the view; it must belong to the set of element types supported by the DLPack bridge, otherwise the conversion returns false. |
| `Extents` | The extents type of the view; its rank() determines the rank of the output tensor. |
| `Layout` | The layout mapping type of the view; its per-dimension strides are written into the stride array of the output tensor. |
| `Accessor` | The accessor type of the view; it participates in deduction together with the mdspan and does not change the conversion result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `view` | Input | The mdspan view to convert (non-owning); its data pointer must be non-null, otherwise false is returned. The conversion only borrows its data address and does not acquire ownership of the storage. |
| `device_type` | Input | The device type recorded by the output tensor (a DLDeviceType enumerator); only kDLCPU and kDLExtDev are accepted, and other values return false. |
| `device_id` | Input | The device number (int) recorded by the output tensor; it is written verbatim into its device description without validation. |
| `output` | Output | The output object (dlpack_tensor<Extents::rank()>) that receives the DLPack tensor description; on success the data pointer, device, number of dimensions, dtype, and per-dimension shapes and strides are written (byte_offset is set to 0), and on failure it is left unchanged. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- The DLPack bridge is provided only when the real `<dlpack/dlpack.h>` can be included, and it is called only on the Host; the conversion neither allocates nor takes over data.

- The output data points to the address corresponding to the view's logical zero coordinates, including the origin offset of the relaxed layout; byte_offset is 0, and the shapes and strides are held by output.
- The exported tensor only borrows the data; both output and the original data must cover the usage period. The device type must be specified by the caller according to the actual storage, and the per-dimension sizes and strides must be representable by DLPack's int64_t.


## Example

The DLPack bridge interface is available only when the DLPack headers are provided; the following Host snippet borrows view and tensor storage managed by the caller.

```cpp
#include <asc/mdspan>
#include <dlpack/dlpack.h>

bool example()
{
    int values[4] = {10, 20, 30, 40};
    using extents_type = asc::std::extents<asc::std::size_t, 2, 2>;
    asc::host_mdspan<int, extents_type> view(values);
    asc::dlpack_tensor<2> output;
    if (!asc::to_dlpack_tensor(view, kDLCPU, 0, output)) return false;
    const DLTensor tensor = output.get();
    return tensor.data == values && tensor.device.device_type == kDLCPU && tensor.device.device_id == 0 &&
        tensor.ndim == 2 && tensor.dtype.code == kDLInt && tensor.dtype.bits == 32 && tensor.dtype.lanes == 1 &&
        tensor.shape[0] == 2 && tensor.shape[1] == 2 && tensor.strides[0] == 2 && tensor.strides[1] == 1 &&
        tensor.byte_offset == 0 && static_cast<int*>(tensor.data)[3] == 40;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
