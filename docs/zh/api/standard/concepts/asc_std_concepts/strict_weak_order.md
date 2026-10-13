# asc::std::strict_weak_order

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

`asc::std::strict_weak_order`在C++20及以上模式约束构成严格弱序的二元关系：在满足`relation`的四种调用组合均有效的基础上，语义上还要求非自反（`r(a, a)`为假）、传递，且不可比关系（既非`r(a, b)`亦非`r(b, a)`）自身具有传递性。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

```cpp
namespace asc::std {
template<class Rp, class T, class U> concept strict_weak_order;
} // namespace asc::std
```

## 约束说明

- 提供完整的公开C++20 concepts集合。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/concepts>

static_assert(asc::std::strict_weak_order<bool (*)(int, int), int, int>);
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
