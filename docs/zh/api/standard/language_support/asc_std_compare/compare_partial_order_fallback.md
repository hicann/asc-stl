# asc::std::compare_partial_order_fallback

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

`asc::std::compare_partial_order_fallback`是比较函数对象类型；构造对象后可调用，优先使用可用的三路比较，否则根据`==`和`<`合成`asc::std::partial_ordering`。

标准语义参考：[cppreference `compare`](https://en.cppreference.com/w/cpp/header/compare)。

## 声明

当前版本以类类型公开此接口；先构造函数对象，再传入两个值。

```cpp
namespace asc::std {
struct compare_partial_order_fallback {
    template <class T, class U>
    [[nodiscard]] constexpr partial_ordering operator()(T&& left, U&& right) const;
};
} // namespace asc::std
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的第一个值。 |
| `right` | 输入 | 参与比较的第二个值。 |

## 返回值说明

返回`asc::std::partial_ordering`比较类别值；偏序比较可返回无序。

| 调用形式 | 返回类型 |
| --- | --- |
| 两个值 | `asc::std::partial_ordering` |

## 约束说明

- 实参必须支持适用的三路比较，或同时支持相等与小于比较。

## 调用示例

以下片段构造函数对象，再比较两个整数。

```cpp
#include <asc/std/compare>

inline constexpr auto example = asc::std::compare_partial_order_fallback{}(1, 2);
static_assert(example < 0);
```

## 关联API

- [本头文件的接口列表](asc_std_compare.md)
