# asc::std::derived_from

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

`asc::std::derived_from` 在 C++20 及以上模式约束 `Derived`（派生类型）公有且无歧义地派生自 `Base`（基类型），具体判据为 `is_base_of_v<Base, Derived>` 与 `is_convertible_v<const volatile Derived*, const volatile Base*>` 同时成立。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

```cpp
template<class Derived, class Base> concept asc::std::derived_from
```

## 约束说明

- 仅在 C++20 及以上模式（`__cpp_concepts >= 201907L`）可用
- 概念成立条件：`Derived` 与 `Base` 是同一类型，或 `Derived` 公开且无歧义地继承自 `Base`（可访问基类且无歧义路径）

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/concepts>

struct base {};
struct derived : base {};
static_assert(asc::std::derived_from<derived, base>);
```
