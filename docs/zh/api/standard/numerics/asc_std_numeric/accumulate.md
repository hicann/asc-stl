# asc::std::accumulate

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

头文件路径为：`<asc/std/numeric>`。

`asc::std::accumulate` 从初值开始按顺序归约输入范围。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class InputIterator, class T, class BinaryOperation> [[nodiscard]] constexpr T asc::std::accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op);
```

### 原型 2

```cpp
template<class InputIterator, class T> [[nodiscard]] constexpr T asc::std::accumulate(InputIterator first, InputIterator last, T init);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryOperation` | 逐步合并累加值的二元运算可调用对象类型：接受两个 T 值并返回可转换为 T 的结果。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `binary_op` | 输入 | 二元归约运算对象，按 binary_op(当前累加值, 当前元素) 逐步合并初值与各元素；省略该参数的重载使用 operator+。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T` | 返回输入值按接口规定运算后的数值结果。 |
| 原型 2 | `T` | 返回输入值按接口规定运算后的数值结果。 |

## 约束说明

- 提供顺序迭代器/值重载
- 本族中标准定义的执行策略重载采用顺序执行语义

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::accumulate(input, input + 4, 0);
}
```
