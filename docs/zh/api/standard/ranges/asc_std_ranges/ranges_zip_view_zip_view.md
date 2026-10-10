# asc::std::ranges::zip_view::zip_view

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

`asc::std::ranges::zip_view::zip_view` 按本页所列构造形态初始化 `zip_view` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
zip_view();
```

### 原型 2

```cpp
constexpr zip_view(Views... base);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 提供“按本页所列构造形态初始化 `zip_view` 对象”所需的输入对象；类型须满足所选原型约束。 |

## 约束说明

- 七个列出名称
- 有限repeat、两路random-access+sized zip引用写回、单次range|closure
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::zip_view<asc::std::ranges::single_view<int>, asc::std::ranges::single_view<int>> value{};
    (void)value;
}
```
