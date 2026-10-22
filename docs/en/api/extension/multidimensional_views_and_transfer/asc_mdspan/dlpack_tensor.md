# asc::dlpack_tensor

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

`asc::dlpack_tensor` stores DLPack tensor metadata and its associated data pointer.

## Declaration

```cpp
namespace asc {
template <asc::std::size_t Rank>
class dlpack_tensor;
}  // namespace asc
```

## Constraints

- Use only in a Host environment that provides the real DLPack headers; the object owns the shape and stride arrays but not the data. The metadata pointer in the return value of get must be used while holder is alive.


## Example

The following Host example requires the real DLPack development headers. `holder` holds the shape/stride metadata but does not own `values`; both must outlive the exported `DLTensor`.

```cpp
#include <dlpack/dlpack.h>
#include <asc/mdspan>

bool example()
{
    int values[] = {2, 4, 6};
    using Extents = asc::std::extents<int, 3>;
    asc::std::mdspan<int, Extents> view(values);
    asc::dlpack_tensor<1> holder;
    if (!asc::to_dlpack_tensor(view, kDLCPU, 0, holder))
        return false;
    const DLTensor tensor = holder.get();
    return tensor.data == values && tensor.ndim == 1 && tensor.shape[0] == 3;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
