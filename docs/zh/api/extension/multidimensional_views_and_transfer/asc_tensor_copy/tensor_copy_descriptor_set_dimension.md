# asc::tensor_copy_descriptor::set_dimension

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

头文件路径为：`<asc/tensor_copy>`。

`asc::tensor_copy_descriptor::set_dimension`设置指定维度的范围、源/目标步长及两侧填充。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr void set_dimension(unsigned int dimension, unsigned int extent, unsigned int source_stride,
    unsigned int destination_stride, unsigned int left_padding, unsigned int right_padding) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `dimension` | 输入 | 待设置的维度索引，从0起计（最内维为Rank-1）；不小于Rank时本次调用不改动描述符的任何字段。 |
| `extent` | 输入 | 该维度参与搬运的有效元素个数，以元素计（uint32_t）；描述符校验通过须其为非零值。 |
| `source_stride` | 输入 | 该维度源端（GM）相邻元素跨距，以元素计（uint32_t）；描述符校验通过须其为非零值。 |
| `destination_stride` | 输入 | 该维度目标端（UB）相邻元素跨距，以元素计（uint32_t）；描述符校验通过须其为非零值。 |
| `left_padding` | 输入 | 该维度目标端左侧填充的元素个数（uint32_t），搬运时以fill_value写入。 |
| `right_padding` | 输入 | 该维度目标端右侧填充的元素个数（uint32_t），搬运时以fill_value写入。 |

## 返回值说明

无返回值。

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- `dimension`应小于`Rank`；当前实现对越界索引不写入任何字段。
- 设置仅复制给定数值，不自动执行[validate](tensor_copy_descriptor_validate.md)；实际搬运前须保证有效长度和步长非零、各侧填充不超过255，并通过大小及跨度校验。

## 调用示例

以下Host片段以二维描述符演示设置一个有效维度。

```cpp
#include <asc/tensor_copy>

bool example()
{
    asc::tensor_copy_descriptor<2> descriptor;
    descriptor.set_dimension(0, 2, 2, 2, 0, 0);
    descriptor.set_dimension(1, 2, 1, 1, 0, 0);
    return descriptor.extent(0) == 2 && descriptor.extent(1) == 2 &&
        descriptor.source_stride(0) == 2 && descriptor.destination_stride(1) == 1 &&
        descriptor.left_padding(0) == 0 && descriptor.right_padding(1) == 0 &&
        descriptor.validate() == asc::tensor_copy_status::success;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
