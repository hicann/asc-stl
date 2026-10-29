# asc::to_host_mdspan

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

`asc::to_host_mdspan`从Host数据指针、范围和步长创建host_mdspan。

## 函数原型

```cpp
namespace asc {
template <class Element, asc::std::size_t Rank, class Layout = asc::layout_stride_relaxed>
bool to_host_mdspan(const DLTensor& tensor,
    asc::host_mdspan<Element, asc::std::dextents<asc::std::size_t, Rank>, Layout>& output) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Element` | 视图所访问元素的类型；底层存储须包含相应有效对象。 |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Layout` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tensor` | 输入 | 待转换或搬运的张量描述；数据指针、形状和步长须有效。 |
| `output` | 输出 | 提供非拥有多维数据视图；底层存储须在视图使用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- DLPack桥接仅在可包含真实`<dlpack/dlpack.h>`时提供，且仅在Host调用；转换不分配或接管数据。

- Host导入仅接受kDLCPU，GM导入仅接受kDLExtDev；ndim必须等于Rank，非零Rank需要shape。
- 支持float/double及标准有符号、无符号整数的对应DLPack dtype；code、bits和lanes必须匹配（lanes为1），不支持组合返回false。
- data须非空、shape各维非负、byte_offset满足元素自然对齐，偏移与有符号跨度须可表示；所有检查失败均不改output。
- 转换只借用原数据，成功后底层有效存储须覆盖视图访问；负步长要求原张量数据指向正确逻辑原点。

- 默认及Host/GM/UB访问器使用非负元素偏移；手动使用负步长时须通过mapping origin保证所有有效坐标的偏移非负且仍在存储内。
- DLPack导入保留有符号步长，通过重定位句柄并设置非负origin表达反向视图；无法表示的步长跨度返回false且输出不变。


## 调用示例

DLPack桥接接口仅在提供DLPack头文件时可用；以下Host片段借用调用方管理的视图和张量存储。

```cpp
#include <asc/mdspan>
#include <dlpack/dlpack.h>

bool example()
{
    int values[4] = {10, 20, 30, 40};
    int64_t shape[2] = {2, 2};
    int64_t strides[2] = {2, 1};
    DLTensor tensor{};
    tensor.data = values;
    tensor.device = DLDevice{kDLCPU, 0};
    tensor.ndim = 2;
    tensor.dtype = DLDataType{kDLInt, 32, 1};
    tensor.shape = shape;
    tensor.strides = strides;
    using extents_type = asc::std::dextents<asc::std::size_t, 2>;
    asc::host_mdspan<int, extents_type, asc::layout_stride_relaxed> output;
    if (!asc::to_host_mdspan<int, 2>(tensor, output)) return false;
    return output.extent(0) == 2 && output.extent(1) == 2 && output.stride(0) == 2 &&
        output.stride(1) == 1 && output.data_handle() == values && output.mapping()(1, 1) == 3 && &output(1, 1) == values + 3 && output(1, 1) == 40;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
