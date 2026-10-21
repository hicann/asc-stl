# asc::std::equivalence_relation

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

`asc::std::equivalence_relation`判定构成等价关系的二元关系：在满足`relation`的四种调用组合均有效的基础上，语义上还要求`r(a, a)`为真、关系对称（`r(a, b)`蕴含`r(b, a)`）且传递（`r(a, b)`与`r(b, c)`蕴含`r(a, c)`）。编译器不自动证明这些数学性质。

C++17中提供同名`inline constexpr bool`变量模板；启用concepts的C++20及以上提供原生concept。两种形式均可用于`static_assert`，C++17还可与`enable_if`配合使用。受约束模板参数、`requires`及约束偏序仍需要C++20语言支持。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

本公开名称在C++17中为inline constexpr bool变量模板；启用concepts的C++20及以上为原生concept。两种形式模板参数相同。以下以已定义的公开名称查询布尔值，不是概念前置声明；satisfies_equivalence_relation只是示例中的查询名称。

```cpp
template<class R, class T, class U>
inline constexpr bool satisfies_equivalence_relation = asc::std::equivalence_relation<R, T, U>;
```

## 约束说明

- C++17变量模板不参与concept约束偏序。
- 语法条件为relation<R,T,U>；还要求关系自反、对称且传递。编译器不自动证明这些数学性质。
- 同名条件从C++17起可用于static_assert或SFINAE；原生concept、requires及约束偏序需要相应C++20语言支持。
- 条件查询只检查可表达的类型与表达式性质，不实际构造、交换或调用对象，也不替代相应的运行期语义前提。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/concepts>

struct increment { int operator()(int value) const { return value + 1; } };

struct equal { bool operator()(int left, int right) const { return left == right; } };

static_assert(asc::std::equivalence_relation<equal, int, int>);
static_assert(!asc::std::equivalence_relation<increment, int, int>);
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
