# asc::std::ratio_greater_equal_v

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

`asc::std::ratio_greater_equal_v`在编译期判断两个有理数是否满足名称所指的大小关系。

标准语义参考：[cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio)。

## 声明

```cpp
namespace asc::std {
template<class R1, class R2> inline constexpr bool ratio_greater_equal_v = ratio_greater_equal<R1, R2>::value;
} // namespace asc::std
```

## 约束说明

- 分母不得为零；规范化后的分子和分母必须可由`intmax_t`表示。

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/std/ratio>

inline constexpr auto example = asc::std::ratio_greater_equal_v<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>;
```

## 关联API

- [本头文件的接口列表](asc_std_ratio.md)
