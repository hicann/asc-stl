# asc::std::aligned_union::alignment_value

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

头文件路径为：`<asc/std/type_traits>`。

`asc::std::aligned_union::alignment_value`在编译期给出对应类型特征的值或对齐要求。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

`alignment_value`是`aligned_union<Len, First, Types...>`的静态`const size_t`整型常量，可在常量表达式中使用，其值为所有候选类型对齐值的最大值。

```cpp
using storage = asc::std::aligned_union<16, int, float>;
static_assert(storage::alignment_value == (alignof(int) > alignof(float) ? alignof(int) : alignof(float)));
```

## 约束说明

- 类型参数列表必须非空，各候选类型须能用于`sizeof`和`alignof`。
- `alignment_value`取各候选类型对齐值的最大值；存储大小至少为`Len`与各候选类型大小的最大值，并按对齐要求取整。
- 结果是原始存储类型；使用其中存储对象前须正确建立该对象的生命周期，结束后须按其类型销毁。

## 调用示例

以下Host片段用具体类型实参实例化本页类型特征。

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::aligned_union<16, int, float>::alignment_value) == (alignof(int) > alignof(float) ? alignof(int) : alignof(float)));
```

## 关联API

- [`asc::std::aligned_union`](aligned_union.md)
- [本头文件的接口列表](asc_std_type_traits.md)
