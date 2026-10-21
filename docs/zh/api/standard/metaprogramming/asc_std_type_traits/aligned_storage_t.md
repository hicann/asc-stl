# asc::std::aligned_storage_t

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

`asc::std::aligned_storage_t`计算满足指定大小与对齐的原始存储类型，以类型别名形式提供结果。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

声明摘要。默认`Align`采用实现选择的对齐值，可通过`alignof(typename aligned_storage<Len>::type)`查询。

```cpp
namespace asc::std {
template<size_t Len, size_t Align = alignof(typename aligned_storage<Len>::type)>
using aligned_storage_t = typename aligned_storage<Len, Align>::type;
} // namespace asc::std
```

## 约束说明

- 本辅助形式与[`asc::std::aligned_storage`](aligned_storage.md)使用相同的类型前提和判定规则；结果对应特征类的`type`。

## 调用示例

以下Host示例使用独立的预期类型或值检查接口结果。

```cpp
#include <asc/std/type_traits>

using storage_type = asc::std::aligned_storage_t<sizeof(double), alignof(double)>;
static_assert(sizeof(storage_type) >= sizeof(double));
static_assert(alignof(storage_type) >= alignof(double));
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
