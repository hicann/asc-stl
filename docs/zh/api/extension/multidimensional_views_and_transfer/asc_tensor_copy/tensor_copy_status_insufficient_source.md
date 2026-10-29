# asc::tensor_copy_status::insufficient_source

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

`asc::tensor_copy_status::insufficient_source` 表示源视图不足以覆盖 Descriptor 所需元素；在 GM→UB 加载方向，源端地址未满足搬运引擎 32 字节对齐要求时同样返回本状态。

## 声明

所属类型：[`asc::tensor_copy_status`](tensor_copy_status.md)。

```cpp
// asc::tensor_copy_status 类内的声明节选；模板形参和其他成员由所属类提供。
insufficient_source = 4;
```

## 约束说明

- 这是[tensor_copy_status](tensor_copy_status.md)的枚举常量；可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较，读取常量不执行校验或搬运。
- 表示搬运所需的源元素跨度超出源视图容量。
- [tensor_load_async](tensor_load_async.md)还会在源端地址未满足32字节边界时返回此值；本状态不由单独的描述符校验产生。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/tensor_copy>

bool example()
{
    using status = asc::tensor_copy_status;
    const status selected = status::insufficient_source;
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
        selected != status::insufficient_destination &&
        selected != status::invalid_stage;
}
```

## 关联API

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [本头文件的接口列表](asc_tensor_copy.md)
