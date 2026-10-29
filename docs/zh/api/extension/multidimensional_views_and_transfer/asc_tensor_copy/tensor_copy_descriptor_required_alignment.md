# asc::tensor_copy_descriptor::required_alignment

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

`asc::tensor_copy_descriptor::required_alignment`返回描述符最内维填充后的行长度，单位为元素。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr unsigned int required_alignment() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回描述符最内维填充后的行长度，单位为元素。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- 返回最内维`extent + left_padding + right_padding`的元素数，按32位无符号整数计算；超出该类型范围时会回绕。
- 该结果用于描述目标端填充后的行长度，单位是元素；按元素类型换算字节数见[tensor_copy_required_alignment](tensor_copy_required_alignment.md)。
- 本查询不检查描述符或实际地址；搬运两端的32字节地址边界要求与此行长度分别检查。

## 调用示例

以下Host片段以二维描述符演示调用。

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return descriptor.required_alignment() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
