# asc::std::aligned_storage

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

`asc::std::aligned_storage`计算满足指定大小与对齐的原始存储类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

`asc::std::aligned_storage<Len, Align>::type`是至少容纳`Len`字节且满足`Align`对齐的平凡标准布局存储类型。`Align`可省略，默认为实现从支持的基础类型对齐值中选取的不大于`Len`的最大值。

下面展示显式对齐和默认对齐的用法：

```cpp
using ExplicitStorage = asc::std::aligned_storage<16, 8>::type;
using DefaultStorage = asc::std::aligned_storage<16>::type;
```

## 约束说明

- `Len > 0`；显式`Align`须为实现支持的对齐值。
- 存储本身不是已构造的目标对象，放置构造后才能按目标类型访问。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // _t 与 ::type 一致，存储大小按对齐值取整
    static_assert(asc::std::is_same_v<asc::std::aligned_storage_t<16, 4>, asc::std::aligned_storage<16, 4>::type>);
    static_assert(sizeof(asc::std::aligned_storage_t<16, 4>) == 16);
    static_assert(alignof(asc::std::aligned_storage_t<16, 4>) == 4);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
