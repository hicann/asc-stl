# asc::std::ranges::dangling::dangling

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

`asc::std::ranges::dangling::dangling` 按本页所列构造形态初始化 `dangling` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
constexpr dangling();
```

### 原型 2

```cpp
template<class ...Args> constexpr dangling(Args&&... args) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 约束说明

- 支持数组和用户范围，不支持仅由花括号构成的 initializer_list 表达式

## 调用示例

以下 Host 片段使用具体类型演示调用；指针、范围和索引须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::dangling result{};
    (void)result;
}
```
