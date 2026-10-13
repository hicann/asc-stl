# asc::std::ranges::enable_borrowed_range

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

头文件路径为：`<asc/std/string_view>`。

`asc::std::ranges::enable_borrowed_range<basic_string_view<C,T>>`由`<asc/std/string_view>`提供，标准C++20：string_view为借用范围

标准语义参考：[cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view)。

## 声明

```cpp
namespace asc::std::ranges {
template<class CharT, class Traits>
inline constexpr bool enable_borrowed_range<asc::std::basic_string_view<CharT, Traits>> = true;
} // namespace asc::std::ranges
```

这是变量模板特化，值为`true`，表示该类型满足相应视图／借用区间登记。

## 约束说明

- 标准C++20：string_view为借用范围。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/string_view>
#include <asc/std/ranges>

static_assert(asc::std::ranges::enable_borrowed_range<asc::std::span<int>>);
```

## 关联API

- [本头文件的接口列表](asc_std_string_view.md)
