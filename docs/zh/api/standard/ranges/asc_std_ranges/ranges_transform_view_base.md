# asc::std::ranges::transform_view::base

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

`asc::std::ranges::transform_view::base` 返回适配器保存的底层迭代器或对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr View asc::std::ranges::transform_view::base()&&;
```

### 原型 2

```cpp
template<class View2> [[nodiscard]] constexpr View asc::std::ranges::transform_view::base() const&;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `View` | 返回适配器保存的底层迭代器或对象。 |
| 原型 2 | `View` | 返回适配器保存的底层迭代器或对象。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example(asc::std::ranges::transform_view<asc::std::ranges::ref_view<int[4]>, asc::std::identity>& object)
{
    (void)object.base();
}
```
