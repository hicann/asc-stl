# asc::tensor_copy_required_elements

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

`asc::tensor_copy_required_elements` 计算 Descriptor 覆盖的源或目标存储元素数量上界。

## 函数原型

```cpp
template<unsigned Rank> constexpr unsigned long long asc::tensor_copy_required_elements(const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `descriptor` | 输入 | 描述张量形状、步长与搬运方向的对象；提交前须通过校验。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unsigned long long` | 返回描述符覆盖的元素数量。 |

## 约束说明

- 描述符及状态类型可在 Host、AI Core SIMD 编程 和 AI Core SIMT 编程中使用
- Rank 为 1 至 5
- 维度和步长采用 uint32_t，校验零维、零步长、大小溢出与对齐要求，校验本身不启动异步搬运

## 调用示例

以下片段以二维无填充描述符展示查询或校验；实际存储须满足描述符范围。

```cpp
#include <asc/tensor_copy>

decltype(auto) example()
{
    unsigned int extents[2] = {2, 2};
    unsigned int strides[2] = {2, 1};
    unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::tensor_copy_required_elements(descriptor);
}
```
