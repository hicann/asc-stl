# asc::tensor_copy_descriptor::rank

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

`asc::tensor_copy_descriptor::rank`返回Tensor Copy Descriptor的编译期维数。

## 函数原型

以下为`asc::tensor_copy_descriptor<Rank>`类内声明，Rank由所属类模板提供。

```cpp
constexpr unsigned int rank() const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回Tensor Copy Descriptor的编译期维数。 |

## 约束说明

- 可在Host、AI Core SIMD编程和AI Core SIMT编程中调用；本操作同步处理描述符，不启动数据搬运。
- 返回编译期模板参数`Rank`，其取值为1至5；不要求描述符已通过校验。

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
    return descriptor.rank() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
