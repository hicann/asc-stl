# asc::std::uniform_int_distribution::uniform_int_distribution

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

头文件路径为：`<asc/std/random>`。

`asc::std::uniform_int_distribution::uniform_int_distribution` 按本页所列构造形态初始化 `uniform_int_distribution` 对象。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

### 原型 1

```cpp
constexpr uniform_int_distribution() noexcept;
```

### 原型 2

```cpp
constexpr uniform_int_distribution(const param_type& parameters) noexcept;
```

### 原型 3

```cpp
constexpr uniform_int_distribution(result_type minimum, result_type maximum) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `parameters` | 输入 | 分布参数对象引用；以其保存的闭区间参数初始化本分布。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `minimum` | 输入 | 闭采样区间的下界；生成值不小于该值。 |
| `maximum` | 输入 | 闭采样区间的上界；生成值不大于该值。 |

## 约束说明

- 支持全部标准整数结果类型

## 调用示例

以下 Host 片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/random>

void example()
{
    asc::std::uniform_int_distribution<int> distribution{};
    (void)distribution.min();
}
```
