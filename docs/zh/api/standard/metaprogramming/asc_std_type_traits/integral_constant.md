# asc::std::integral_constant

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

`asc::std::integral_constant`以类型承载编译期常量值。

标准语义参考：[cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits)。

## 声明

```cpp
namespace asc::std {
template<class T, T V> struct integral_constant;
} // namespace asc::std
```

## 约束说明

- 提供特征类及其对应的 _v辅助形式。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    using two = asc::std::integral_constant<int, 2>;
    // ::value 携带编译期常量
    static_assert(two::value == 2);
    static_assert(asc::std::is_same_v<two::value_type, int>);
    static_assert(asc::std::is_same_v<two::type, two>); // type 即自身
    // bool_constant 即 integral_constant<bool, B>
    static_assert(asc::std::bool_constant<true>::value);
    // 反例：false_type 取值为假
    static_assert(!asc::std::false_type::value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_type_traits.md)
