# asc::tensor_copy_descriptor::destination_stride

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

`asc::tensor_copy_descriptor::destination_stride`返回指定维度的目标存储步长。

## 函数原型

```cpp
constexpr unsigned int asc::tensor_copy_descriptor<Rank>::destination_stride(unsigned int dimension) const noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 描述符的张量秩（维度数量），为1至5的编译期无符号整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `dimension` | 输入 | 待查询的维度索引，从0起计（最内维为Rank-1）；小于Rank时返回该维度目标端（UB）的元素步长，越界时返回0。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned int` | 返回指定维度的目标存储步长。 |

## 约束说明

- 描述符及状态类型可在Host、AI Core SIMD编程 和AI Core SIMT编程中使用。
- Rank为1至5。
- 维度和步长采用uint32_t，校验零维、零步长、大小溢出与对齐要求，校验本身不启动异步搬运。

## 调用示例

以下Host片段以二维描述符演示调用；调用方须保证维度和描述符有效。

```cpp
#include <asc/tensor_copy>

decltype(auto) example(const asc::tensor_copy_descriptor<2>& descriptor)
{
    // dimension 必须小于描述符的秩。
    auto value = descriptor.destination_stride(0);
    return value;
}
```

## 关联API

- [本头文件的接口列表](asc_tensor_copy.md)
