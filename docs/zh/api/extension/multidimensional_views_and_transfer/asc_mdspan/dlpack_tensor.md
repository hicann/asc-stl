# asc::dlpack_tensor

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/mdspan>`。

`asc::dlpack_tensor`保存DLPack张量元数据及其关联的数据指针。

## 声明

```cpp
namespace asc {
template<asc::std::size_t Rank> class dlpack_tensor;
} // namespace asc
```

## 约束说明

- 提供Host和GM视图以及AI Core SIMD编程UB视图。
- 允许有符号步长。
- 可选的Host DLPack桥接不抛出异常。

## 调用示例

以下Host示例需要真实DLPack开发头文件。`holder`持有形状／步长元数据，但不拥有`values`；二者都须比导出的`DLTensor`使用期更长。

```cpp
#include <dlpack/dlpack.h>
#include <asc/mdspan>

bool example()
{
    int values[] = {2, 4, 6};
    using Extents = asc::std::extents<int, 3>;
    asc::std::mdspan<int, Extents> view(values);
    asc::dlpack_tensor<1> holder;
    if (!asc::to_dlpack_tensor(view, kDLCPU, 0, holder)) return false;
    const DLTensor tensor = holder.get();
    return tensor.data == values && tensor.ndim == 1 && tensor.shape[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
