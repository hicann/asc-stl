# WCHAR_MAX

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

头文件路径为：`<asc/std/cwchar>`。

`WCHAR_MAX`给出宽字符类型的最大值。

该接口的可用位置为Host（完整接口）、Device（C locale相关接口）。

标准语义参考：[cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar)。

## 声明

Host的宏定义由系统`<cwchar>`提供。Device仅在工具链未预先定义对应宏时采用以下回退。

```cpp
#ifndef WCHAR_MAX
#define WCHAR_MAX __WCHAR_MAX__
#endif
```

## 约束说明

- Host行为遵循系统`<cwchar>`提供的同名接口；字符转换和排序受当前C语言区域设置影响。
- 类型宽度、取值范围和哨兵值由编译目标决定，不应假设与另一平台相同。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cwchar>

#ifndef WCHAR_MAX
#error "WCHAR_MAX is required by this public Header"
#endif
```

## 关联API

- [本头文件的接口列表](asc_std_cwchar.md)
