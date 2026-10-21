# asc::tensor_copy_status::success

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

`asc::tensor_copy_status::success`表示Tensor Copy Descriptor或异步加载校验成功。

## 声明

所属类型：[`asc::tensor_copy_status`](tensor_copy_status.md)。

```cpp
// asc::tensor_copy_status 类内的声明节选；模板形参和其他成员由所属类提供。
success = 0;
```

## 约束说明

- 这是[tensor_copy_status](tensor_copy_status.md)的枚举常量；可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较，读取常量不执行校验或搬运。
- 对描述符校验而言，表示该次校验通过；它不检查实际存储或端点地址。
- 对[tensor_load_async](tensor_load_async.md)或[tensor_store_async](tensor_store_async.md)而言，表示检查通过并已提交异步搬运；数据完成和缓冲复用仍须按流水线接口等待。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/tensor_copy>

auto value = asc::tensor_copy_status::success;
```

## 关联API

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [本头文件的接口列表](asc_tensor_copy.md)
