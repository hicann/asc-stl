# CANN_ASC_STL_HAS_SUBMDSPAN

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

头文件路径为：`<asc/std/version>`。

`CANN_ASC_STL_HAS_SUBMDSPAN`查询ASC-STL是否提供submdspan已列出的切片接口。

## 声明

该对象式宏从C++17起可使用，展开为值为0或1的整型常量表达式，可用于`#if`条件编译。

## 约束说明

- 值描述当前配置中ASC-STL已选接口子集的能力，不表示整个ISO标准版本的完整实现，也不描述Host的`std`命名空间。
- 值为1时，具体操作仍须满足相应API的类型、重载、执行位置、资源与常量求值约束。

## 调用示例

以下片段检查能力查询宏的取值形式；具体设施的使用方法见对应API页面。

```cpp
#include <asc/std/version>

static_assert(CANN_ASC_STL_HAS_SUBMDSPAN == 0 || CANN_ASC_STL_HAS_SUBMDSPAN == 1);
```

## 关联API

- [语言模式与兼容性](../../../../guide/cpp_compatibility.md)
- [本头文件的接口列表](asc_std_version.md)
