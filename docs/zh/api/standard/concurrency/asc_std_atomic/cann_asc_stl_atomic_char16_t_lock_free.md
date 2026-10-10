# CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE

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

头文件路径为：`<asc/std/atomic>`。

`CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE` 报告对应原子类型是否始终使用无锁实现的能力等级。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
#define CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE 2
```

## 约束说明

- 11个CANN_ASC_STL_ATOMIC_*_LOCK_FREE产品宏
- 已交付整数/字符为2，未交付pointer为0
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/atomic>

#ifndef CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE
#error "CANN_ASC_STL_ATOMIC_CHAR16_T_LOCK_FREE is required by this public Header"
#endif
```
