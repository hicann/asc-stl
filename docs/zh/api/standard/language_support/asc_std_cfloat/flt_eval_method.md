# FLT_EVAL_METHOD

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

`FLT_EVAL_METHOD`说明浮点表达式求值采用的精度方法。

标准语义参考：[cppreference `cfloat`](https://en.cppreference.com/w/cpp/header/cfloat)。

## 声明

本宏由平台头文件提供，公共头文件保留其拼写和值，不另造替代宏名。

```cpp
#include <asc/std/cfloat>
```

## 约束说明

- 仅提供编译器ABI实际支持的宏。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/cfloat>
#include <asc/std/type_traits>

static_assert(asc::std::is_same_v<decltype(FLT_EVAL_METHOD), int>);
```

## 关联API

- [本头文件的接口列表](asc_std_cfloat.md)
