# asc::std::ranges::output_range

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::output_range`判定类型或表达式是否满足`output_range`的要求。

C++17中提供同名`inline constexpr bool`变量模板；C++20及以上提供concept。两种形式均可用于`static_assert`，C++17还可与`enable_if`配合使用。受约束模板参数、`requires`及约束偏序仍需要C++20语言支持。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

以下为C++20及以上的concept声明摘要；C++17变量模板具有相同的模板参数和判定条件。

```cpp
namespace asc::std::ranges {
template<class Rp, class T> concept output_range;
} // namespace asc::std::ranges
```

## 约束说明

- 范围判定在C++17中作为布尔常量使用；借用、连续性和迭代器类别仍须满足各谓词的语义要求。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::output_range<int (&)[4], int>);
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
