# asc::std::inner_product

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

`asc::std::inner_product` 对两个范围逐项组合并从初值归约结果。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2> [[nodiscard]] constexpr T asc::std::inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2);
```

### 原型 2

```cpp
template<class InputIterator1, class InputIterator2, class T> [[nodiscard]] constexpr T asc::std::inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |
| `BinaryOperation1` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `BinaryOperation2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |
| `init` | 输入 | 提供“对两个范围逐项组合并从初值归约结果”所需的输入对象；类型须满足所选原型约束。 |
| `binary_op1` | 输入 | 提供“对两个范围逐项组合并从初值归约结果”所需的输入对象；类型须满足所选原型约束。 |
| `binary_op2` | 输入 | 提供“对两个范围逐项组合并从初值归约结果”所需的输入对象；类型须满足所选原型约束。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |
| `init` | 输入 | 提供“对两个范围逐项组合并从初值归约结果”所需的输入对象；类型须满足所选原型约束。 |

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
    return asc::std::inner_product(input, input + 4, input, 0);
}
```
