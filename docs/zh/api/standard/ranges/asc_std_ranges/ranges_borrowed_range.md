# asc::std::ranges::borrowed_range

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

`asc::std::ranges::borrowed_range`检查以下范围条件：满足range，且T为左值引用，或remove_cvref_t<T>启用了enable_borrowed_range；允许从临时范围对象取得不依赖该对象寿命的迭代器。

C++17中提供同名`inline constexpr bool`变量模板；启用concepts的C++20及以上提供原生concept。两种形式均可用于`static_assert`，C++17还可与`enable_if`配合使用。受约束模板参数、`requires`及约束偏序仍需要C++20语言支持。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

C++17中本公开名称为inline constexpr bool变量模板，启用concepts的C++20中为原生concept。以下以同一公开名称查询其布尔值，不是重新声明该接口；satisfies_borrowed_range仅为示例查询名称。

```cpp
template<class T>
inline constexpr bool satisfies_borrowed_range = asc::std::ranges::borrowed_range<T>;
```

## 约束说明

- 满足range，且T为左值引用，或remove_cvref_t<T>启用了enable_borrowed_range；允许从临时范围对象取得不依赖该对象寿命的迭代器。
- C++17的同名布尔模板可用于static_assert或SFINAE；原生concept语法及约束归约需要相应C++20语言能力。
- 编译期条件成立仍要求使用者遵守迭代器有效期、复杂度及相应语义要求。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::borrowed_range<int (&)[3]>);
static_assert(!asc::std::ranges::borrowed_range<int[3]>);
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
