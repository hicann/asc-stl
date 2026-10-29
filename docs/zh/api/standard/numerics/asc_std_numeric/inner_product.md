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

`asc::std::inner_product`对两个范围逐项组合并从初值归约结果。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T, class BinaryOperation1, class BinaryOperation2> [[nodiscard]] constexpr T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class InputIterator1, class InputIterator2, class T> [[nodiscard]] constexpr T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryOperation1` | 把逐项组合结果并入累加值的二元归约运算可调用对象类型。 |
| `BinaryOperation2` | 组合两个输入范围对应位置元素的二元变换可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 第一个输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 第一个输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 第二个输入范围的起始迭代器；该范围长度不得小于第一个范围。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `binary_op1` | 输入 | 二元归约运算对象，把binary_op2组合两个范围对应元素的结果并入当前累加值。 |
| `binary_op2` | 输入 | 二元组合运算对象，作用于两个范围中对应位置的元素；省略该参数的重载使用逐项相乘。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 第一个输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 第一个输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 第二个输入范围的起始迭代器；该范围长度不得小于第一个范围。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回输入值按接口规定运算后的数值结果。 |
| 原型2 | `T` | 返回输入值按接口规定运算后的数值结果。 |

## 约束说明

- `[first1, last1)`须为有效的可读输入范围，`first2`起的第二个范围至少具有相同数量的可读元素。
- 默认重载逐项相乘并累加；自定义重载先调用`binary_op2`组合对应元素，再调用`binary_op1`更新累加值。
- 输入按迭代顺序处理，运算结果须可赋回`T`；运算不得修改输入范围或使迭代器失效。

## 调用示例

以下示例将数组与自身逐项相乘后累加，返回30。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::inner_product(input, input + 4, input, 0);
}

bool verify_example()
{
    return example() == 30;
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
