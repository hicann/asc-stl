# asc::std::different_from

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

`asc::std::different_from`判定去掉引用和cv限定后的`T`与`U`是否为不同类型，适用于排除同一基础类型的模板候选。例如`int`与`const int&`不是不同的基础类型。

C++17中提供同名`inline constexpr bool`变量模板；启用concepts的C++20及以上提供原生concept。两种形式均可用于`static_assert`，C++17还可与`enable_if`配合使用。受约束模板参数、`requires`及约束偏序仍需要C++20语言支持。

标准语义参考：[cppreference `concepts`](https://en.cppreference.com/w/cpp/header/concepts)。

## 声明

本公开名称在C++17中为inline constexpr bool变量模板；启用concepts的C++20及以上为原生concept。两种形式模板参数相同。以下以已定义的公开名称查询布尔值，不是概念前置声明；satisfies_different_from只是示例中的查询名称。

```cpp
template<class T, class U>
inline constexpr bool satisfies_different_from = asc::std::different_from<T, U>;
```

## 约束说明

- C++17变量模板不参与concept约束偏序。
- 移除两类型的引用和cv限定后，两者不满足same_as；例如int与const int&不是不同的基础类型。
- 同名条件从C++17起可用于static_assert或SFINAE；原生concept、requires及约束偏序需要相应C++20语言支持。
- 条件查询只检查可表达的类型与表达式性质，不实际构造、交换或调用对象，也不替代相应的运行期语义前提。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/concepts>

static_assert(asc::std::different_from<int, long>);
static_assert(!asc::std::different_from<int, const int&>);
```

## 关联API

- [本头文件的接口列表](asc_std_concepts.md)
