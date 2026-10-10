# asc::std::compare_weak_order_fallback

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

头文件路径为：`<asc/std/compare>`。

`asc::std::compare_weak_order_fallback` 是可直接调用的比较函数对象；优先使用可用的三路比较，否则根据 `==` 和 `<` 合成 `asc::std::weak_ordering`。

标准语义参考：[cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
asc::std::compare_weak_order_fallback(left, right)
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的第一个值。 |
| `right` | 输入 | 参与比较的第二个值。 |

## 返回值说明

返回 `asc::std::weak_ordering` 比较类别值。

| 调用形式 | 返回类型 |
| --- | --- |
| 两个值 | `asc::std::weak_ordering` |

## 约束说明

- 实参必须支持适用的三路比较，或同时支持相等与小于比较。

## 调用示例

以下片段通过头文件提供的函数对象直接比较两个整数。

```cpp
#include <asc/std/compare>

inline constexpr auto example = asc::std::compare_weak_order_fallback(1, 2);
```
