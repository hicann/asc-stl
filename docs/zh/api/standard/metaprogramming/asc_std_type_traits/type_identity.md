# asc::std::type_identity

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

`asc::std::type_identity`保留原始类型以延迟或禁止模板参数推导。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class T> struct type_identity;
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
    // 正例：type_identity 原样返回传入的类型
    static_assert(asc::std::is_same_v<asc::std::type_identity_t<int>, int>);
    static_assert(asc::std::is_same_v<typename asc::std::type_identity<const float>::type, const float>);
    // 反例：type_identity_t<int> 不是 long
    static_assert(!asc::std::is_same_v<asc::std::type_identity_t<int>, long>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
