# asc::tensor_copy_status::zero_extent

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

`asc::tensor_copy_status::zero_extent`表示至少一个Tensor维度的有效范围为零。

## 声明

所属类型：[`asc::tensor_copy_status`](tensor_copy_status.md)。

```cpp
// asc::tensor_copy_status 类内的声明节选；模板形参和其他成员由所属类提供。
zero_extent = 1;
```

## 约束说明

- 这是[tensor_copy_status](tensor_copy_status.md)的枚举常量；可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较，读取常量不执行校验或搬运。
- 表示描述符校验发现某一维的有效元素个数为零；修改对应维度后须重新校验。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/tensor_copy>

bool example()
{
    using status = asc::tensor_copy_status;
    const status selected = status::zero_extent;
    const status all[] = {
        status::success,
        status::zero_extent,
        status::zero_stride,
        status::size_overflow,
        status::insufficient_source,
        status::insufficient_destination,
        status::invalid_stage
    };
    for (unsigned left = 0; left < 7; ++left) {
        for (unsigned right = left + 1; right < 7; ++right) {
            if (all[left] == all[right]) return false;
        }
    }
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    descriptor.set_dimension(0, 0, 2, 2, 0, 0);
    return descriptor.validate() == selected;
}
```

## 关联API

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [本头文件的接口列表](asc_tensor_copy.md)
