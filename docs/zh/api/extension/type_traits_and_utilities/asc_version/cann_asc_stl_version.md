# CANN_ASC_STL_VERSION

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

头文件路径为：`<asc/version>`。

`CANN_ASC_STL_VERSION` 使用 `主版本号 × 10000 + 次版本号 × 100 + 修订号` 编码完整产品版本，当前值为 10000。

## 声明

```cpp
#define CANN_ASC_STL_VERSION 10000
```

## 约束说明

- 提供产品版本和实际交付能力宏

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/version>

#ifndef CANN_ASC_STL_VERSION
#error "CANN_ASC_STL_VERSION is required by this public Header"
#endif
```
