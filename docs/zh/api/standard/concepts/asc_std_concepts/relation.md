# asc::std::relation

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

`asc::std::relation` 在 C++20 及以上模式约束可调用对象 `R` 在 `T` 与 `U` 两个取值域上构成二元关系：设 `r` 为 `R` 类型的表达式、`a` 为 `T` 类型、`b` 为 `U` 类型，则调用组合 `r(a, a)`、`r(b, b)`、`r(a, b)`、`r(b, a)` 均有效且返回结果可转换为 `bool`；`equivalence_relation`、`strict_weak_order` 等语义概念在此之上进一步施加等价关系或严格弱序约束。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

```cpp
template<class R, class T, class U> concept asc::std::relation
```

## 约束说明

- 提供完整的公开 C++20 concepts 集合

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/concepts>

static_assert(asc::std::relation<bool (*)(int, int), int, int>);
```
