# asc::tensor_copy_status::invalid_stage

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

`asc::tensor_copy_status::invalid_stage`表示指定Pipeline流水级不存在。

## 声明

所属类型：[`asc::tensor_copy_status`](tensor_copy_status.md)。

```cpp
// asc::tensor_copy_status 类内的声明节选；模板形参和其他成员由所属类提供。
invalid_stage = 6;
```

## 约束说明

- 这是[tensor_copy_status](tensor_copy_status.md)的枚举常量；可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较，读取常量不执行校验或搬运。
- 表示传给搬运接口的`stage >= pipeline.stages()`；须选取有效流水级后再提交。
- 本状态由搬运接口产生，单独的描述符校验不读取流水线状态。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/tensor_copy>

bool example()
{
    using status = asc::tensor_copy_status;
    const status selected = status::invalid_stage;
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
    // These transfer-only results are distinct status tags; no transfer runs on Host.
    return selected != status::success &&
        selected != status::zero_extent &&
        selected != status::zero_stride &&
        selected != status::size_overflow &&
        selected != status::insufficient_source &&
        selected != status::insufficient_destination;
}
```

## 关联API

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [本头文件的接口列表](asc_tensor_copy.md)
