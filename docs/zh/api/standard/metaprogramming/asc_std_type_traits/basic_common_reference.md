# asc::std::basic_common_reference

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

`basic_common_reference`是用户特化的公共引用类型计算点，接收两个类型及其限定传播模板。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class, class, template<...> class, template<...> class, class> struct basic_common_reference;
} // namespace asc::std
```

## 约束说明

- 提供特征类以及标准的 _t、_v辅助形式。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

struct Width {};
struct Height {};

// 针对自有类型偏特化自定义点，指定公共引用类型
namespace asc::std {
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<Width, Height, TQual, UQual> {
    using type = Width;
};
}  // namespace asc::std

void use_trait()
{
    // 特化生效：common_reference 命中自定义的公共引用类型
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width, Height>, Width>);
    // 带左值引用限定的组合同样路由到该特化
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width&, Height&>, Width>);
    // 内建类型不受该特化影响，仍按常规规则求公共引用类型
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<int, long>, long>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
