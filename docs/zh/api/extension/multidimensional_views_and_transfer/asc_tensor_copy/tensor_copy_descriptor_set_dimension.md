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

`asc::tensor_copy_descriptor::set_dimension` 设置指定维度的范围、源/目标步长及两侧填充。

## 函数原型

```cpp
constexpr void asc::tensor_copy_descriptor<Rank>::set_dimension(unsigned int dimension, unsigned int extent, unsigned int source_stride, unsigned int destination_stride, unsigned int left_padding, unsigned int right_padding) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `dimension` | 输入 | 指定“设置指定维度的范围、源/目标步长及两侧填充”使用的标量值；取值须满足声明和约束。 |
| `extent` | 输入 | 指定“设置指定维度的范围、源/目标步长及两侧填充”使用的标量值；取值须满足声明和约束。 |
| `source_stride` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |
| `destination_stride` | 输出 | 用于接收结果的目标存储。异步操作完成前，其存储须保持有效。 |
| `left_padding` | 输入 | 指定“设置指定维度的范围、源/目标步长及两侧填充”使用的标量值；取值须满足声明和约束。 |
| `right_padding` | 输入 | 指定“设置指定维度的范围、源/目标步长及两侧填充”使用的标量值；取值须满足声明和约束。 |

## 返回值说明

无返回值。

## 约束说明

- 描述符及状态类型可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Rank 为 1 至 5
- 维度和步长采用 uint32_t，校验零维、零步长、大小溢出与对齐要求，校验本身不启动异步搬运

## 调用示例

以下 Host 片段以二维描述符演示设置一个有效维度。

```cpp
#include <asc/tensor_copy>

void example()
{
    asc::tensor_copy_descriptor<2> descriptor{};
    descriptor.set_dimension(0, 4, 4, 4, 0, 0);
}
```
