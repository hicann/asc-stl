# asc::std::ratio_less

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

头文件路径为：`<asc/std/ratio>`。

`asc::std::ratio_less`以编译期有理数表示比例或判断两个比例的大小关系。

标准语义参考：[cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio)。

## 声明

```cpp
namespace asc::std {
template<class R1, class R2> struct ratio_less;
} // namespace asc::std
```

## 约束说明

- 分母不得为零；规范化后的分子和分母必须可由`intmax_t`表示。

## 调用示例

以下Host片段用具体类型实参和`static_assert`验证本页类型特征的结果。

```cpp
#include <asc/std/ratio>

void use_trait()
{
    // 1/3 小于 1/2
    static_assert(asc::std::ratio_less<asc::std::ratio<1, 3>, asc::std::ratio<1, 2>>::value);
    // 负数比较：-1/2 小于 -1/3
    static_assert(asc::std::ratio_less_v<asc::std::ratio<-1, 2>, asc::std::ratio<-1, 3>>);
    // 反例：1/2 不小于 1/3
    static_assert(!asc::std::ratio_less_v<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>);
}
```

## 关联API

- [本头文件的接口列表](asc_std_ratio.md)
