# asc::std::aligned_union

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

`asc::std::aligned_union`计算可容纳所列类型且满足最大对齐的原始存储类型。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<size_t Len, class Type0, class ...Types> struct aligned_union;
} // namespace asc::std
```

## 约束说明

- 提供特征类以及标准的 _t、_v辅助形式。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    using union_type = asc::std::aligned_union<8, char, int>;
    // alignment_value 为各成员对齐的最大值
    static_assert(union_type::alignment_value == alignof(int));
    // _t 与 ::type 一致，存储至少容纳请求长度与各成员大小
    static_assert(asc::std::is_same_v<asc::std::aligned_union_t<8, char, int>, union_type::type>);
    static_assert(sizeof(asc::std::aligned_union_t<8, char, int>) == 8);
    static_assert(alignof(asc::std::aligned_union_t<8, char, int>) == alignof(int));
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
