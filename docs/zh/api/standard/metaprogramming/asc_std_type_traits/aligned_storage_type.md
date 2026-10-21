# asc::std::aligned_storage::type

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

`asc::std::aligned_storage::type`保存满足指定大小和对齐的原始存储类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

所属类型：[`asc::std::aligned_storage`](aligned_storage.md)。

### 原型1

```cpp
// asc::std::aligned_storage 类内的声明节选；模板形参和其他成员由所属类提供。
struct type;
```

### 原型2

```cpp
// asc::std::aligned_storage 类内的声明节选；模板形参和其他成员由所属类提供。
union type;
```

## 约束说明

- 结果提供至少`Len`字节且满足指定`Align`的原始存储类型；其中候选对象的生命周期需由调用方按对应对象规则建立和结束。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using storage_type = typename asc::std::aligned_storage<sizeof(double), alignof(double)>::type;
static_assert(sizeof(storage_type) >= sizeof(double));
static_assert(alignof(storage_type) >= alignof(double));
```

## 关联API

- [`asc::std::aligned_storage`](aligned_storage.md)
- [本头文件的接口列表](asc_std_type_traits.md)
