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
template <class T, class U, template <class> class TQual, template <class> class UQual, class = void>
struct basic_common_reference;
}  // namespace asc::std
```

## 约束说明

- 该主模板作为公共引用计算的定制点，默认不提供结果成员`type`；定制特化通过`TQual`和`UQual`表示相应引用/cv限定，并须满足公共引用语义。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

struct Measure {};
struct Width : Measure {};
struct Height : Measure {};

// 两个自有类型共享Measure基类，定制点保留输入的引用和cv限定。
namespace asc::std {
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<Width, Height, TQual, UQual> {
    using type = common_reference_t<TQual<Measure>, UQual<Measure>>;
};
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<Height, Width, TQual, UQual> : basic_common_reference<Width, Height, UQual, TQual> {};
}  // namespace asc::std

void use_trait()
{
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width, Height>, Measure>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width&, Height&>, Measure&>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<const Width&, Height&>, const Measure&>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Height&, Width&>, Measure&>);
    // 双方均可转换为所选公共引用；不仅检查定制点返回了一个类型名字。
    static_assert(asc::std::is_convertible_v<Width&, asc::std::common_reference_t<Width&, Height&>>);
    static_assert(asc::std::is_convertible_v<Height&, asc::std::common_reference_t<Width&, Height&>>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<int, long>, long>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
