# asc::tensor_copy_status::size_overflow

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

`asc::tensor_copy_status::size_overflow` 表示 Tensor 存储大小计算超出可表示范围，包括元素总量溢出、填充超过 255 与源/目标步长跨度累计溢出。

## 声明

所属类型：[`asc::tensor_copy_status`](tensor_copy_status.md)。

```cpp
// asc::tensor_copy_status 类内的声明节选；模板形参和其他成员由所属类提供。
size_overflow = 3;
```

## 约束说明

- 这是[tensor_copy_status](tensor_copy_status.md)的枚举常量；可在Host、AI Core SIMD编程和AI Core SIMT编程中保存和比较，读取常量不执行校验或搬运。
- 表示大小计算无法满足接口要求，例如填充超过255、填充后元素总量或步长跨度溢出；[tensor_store_async](tensor_store_async.md)还会检查最内维搬运字节长度。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/tensor_copy>

auto value = asc::tensor_copy_status::size_overflow;
```

## 关联API

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [本头文件的接口列表](asc_tensor_copy.md)
