# asc::std::ranges::subrange::prev

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

`asc::std::ranges::subrange::prev` 返回起点向后移动后的新子范围。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

```cpp
template<class It> [[nodiscard]] constexpr subrange<Iter, Sent, Kind> asc::std::ranges::subrange::prev(iter_difference_t<Iter> amount) const;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `It` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `amount` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `subrange<Iter, Sent, Kind>` | 返回起点向后移动后的新子范围。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下 Host 片段使用具体类型演示调用；指针、范围和索引须满足本页约束。

```cpp
#include <asc/std/ranges>

decltype(auto) example(asc::std::ranges::subrange<int*>& range)
{
    // 调用方保证移动后的迭代器仍在原始范围内。
    return range.prev(1);
}
```
