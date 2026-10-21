# asc::make_tensor_copy_descriptor

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

`asc::make_tensor_copy_descriptor`由各维范围、源/目标步长和填充数组构造Tensor Copy Descriptor。

## 函数原型

```cpp
namespace asc {
template <unsigned Rank>
constexpr asc::tensor_copy_descriptor<Rank> [[nodiscard]] make_tensor_copy_descriptor(
    const unsigned int (&extents)[Rank], const unsigned int (&source_strides)[Rank],
    const unsigned int (&destination_strides)[Rank], const unsigned int (&left_padding)[Rank],
    const unsigned int (&right_padding)[Rank]) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 张量的维度数，取值为1至5；每个输入数组均包含`Rank`个元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 各维的有效长度；维度数量和取值范围须满足本页约束。 |
| `source_strides` | 输入 | 各维在源布局中的步长，以元素为单位；数组中的数值在本次调用中复制到描述符。 |
| `destination_strides` | 输入 | 各维在目标布局中的步长，以元素为单位；数组中的数值在本次调用中复制到描述符。 |
| `left_padding` | 输入 | 各维前侧填充的元素个数；0表示该侧不填充。数组须在本次调用期间有效。 |
| `right_padding` | 输入 | 各维后侧填充的元素个数；0表示该侧不填充。数组须在本次调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::tensor_copy_descriptor<Rank>` | 返回描述源、目标形状及步长的张量搬运描述符。 |

## 约束说明

- `Rank`为1至5，最内层维度的索引为`Rank - 1`。
- 五个输入数组须在调用期间有效；函数复制数组数值，不保存数组引用。
- 本函数同步构造描述符，不提交数据搬运，也不自动调用`validate()`。实际搬运前须检查描述符及其数据范围是否满足相应接口要求。
- 描述符可在Host、AI Core SIMD编程和AI Core SIMT编程中构造。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned extents[2] = {2, 3};
    const unsigned strides[2] = {3, 1};
    const unsigned padding[2] = {0, 0};
    const auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return descriptor.extent(0) == 2 && descriptor.extent(1) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
