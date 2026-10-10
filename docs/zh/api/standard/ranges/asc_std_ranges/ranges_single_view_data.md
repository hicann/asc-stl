# asc::std::ranges::single_view::data

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

`asc::std::ranges::single_view::data` 返回所管理或所观察连续存储的首地址。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr T* asc::std::ranges::single_view::data() noexcept;
```

### 原型 2

```cpp
[[nodiscard]] constexpr const T* asc::std::ranges::single_view::data() const noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T *` | 返回所管理或所观察连续存储的首地址。 |
| 原型 2 | `const T *` | 返回所管理或所观察连续存储的首地址。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example(asc::std::ranges::single_view<int>& object)
{
    (void)object.data();
}
```
