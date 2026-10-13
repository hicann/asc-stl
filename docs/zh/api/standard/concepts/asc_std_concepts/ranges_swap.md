# asc::std::ranges::swap

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

头文件路径为：`<asc/std/concepts>`。

`asc::std::ranges::swap`是交换两个值的定制点对象：优先ADL发现的`swap`，其次等长数组逐元素交换，再次用`exchange`做移动交换。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

```cpp
namespace asc::std::ranges {
constexpr swap_fn swap;
} // namespace asc::std::ranges
```

## 约束说明

- 两实参为可交换的左值，或两个等长的元素可交换数组。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/concepts>
#include <asc/std/ranges>

void example()
{
    int lhs = 1;
    int rhs = 2;
    asc::std::ranges::swap(lhs, rhs);
}
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
