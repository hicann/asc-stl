# DECIMAL_DIG

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

头文件路径为：`<asc/std/cfloat>`。

`DECIMAL_DIG`给出浮点值往返转换所需的十进制有效位数。

标准语义参考：[cppreference `cfloat`](https://en.cppreference.com/w/cpp/header/cfloat)。

## 声明

`DECIMAL_DIG`是由`<asc/std/cfloat>`引入的平台`<float.h>`所提供的整型常量宏。具体值由目标平台的浮点格式决定，不应写成固定的替换标识符。

## 约束说明

- 仅提供编译器ABI实际支持的宏。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/std/cfloat>

#ifndef DECIMAL_DIG
#error "DECIMAL_DIG must be provided by asc/std/cfloat"
#endif

static_assert(DECIMAL_DIG > 0);
```

## 关联API

- [本头文件的接口列表](asc_std_cfloat.md)
