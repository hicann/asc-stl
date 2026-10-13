# asc::std::transform_reduce

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

`asc::std::transform_reduce` 先逐项变换再归约结果。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class Input, class T, class BinaryOperation, class UnaryOperation> T asc::std::transform_reduce(asc::device_policy policy, Input first, Input last, T init, BinaryOperation binary_operation, UnaryOperation unary_operation);
```

该原型适用于 `C++17+`，可用位置为 Host。

### 原型 2

```cpp
template<class InputIterator, class T, class BinaryO, class UnaryO> [[nodiscard]] constexpr T asc::std::transform_reduce(InputIterator first, InputIterator last, T initial, BinaryO reduce_operation, UnaryO transform_operation);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 3

```cpp
template<class InputIterator1, class InputIterator2, class T, class BinaryOp1, class BinaryOp2> [[nodiscard]] constexpr T asc::std::transform_reduce(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initial, BinaryOp1 reduce_operation, BinaryOp2 transform_op);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 4

```cpp
template<class InputIterator1, class InputIterator2, class T> [[nodiscard]] constexpr T asc::std::transform_reduce(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T initial);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryOperation` | 把逐项变换结果并入累加值的二元归约运算可调用对象类型。 |
| `UnaryOperation` | 作用于单个输入元素的一元变换可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略，用于指定 Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `binary_operation` | 输入 | 二元归约运算对象，把 unary_operation 作用于当前元素后的结果并入当前累加值。 |
| `unary_operation` | 输入 | 一元变换运算对象，先作用于每个输入元素，再参与归约。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryO` | 把逐项变换结果并入累加值的二元归约运算可调用对象类型。 |
| `UnaryO` | 作用于单个输入元素的一元变换可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `initial` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `reduce_operation` | 输入 | 二元归约运算对象，把逐项变换或组合的结果并入当前累加值。 |
| `transform_operation` | 输入 | 一元变换运算对象，先作用于第一个范围的每个元素，再参与归约。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryOp1` | 把逐项组合结果并入累加值的二元归约运算可调用对象类型。 |
| `BinaryOp2` | 组合两个输入范围对应位置元素的二元变换可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 第一个输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 第一个输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 第二个输入范围的起始迭代器；该范围长度不得小于第一个范围。 |
| `initial` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `reduce_operation` | 输入 | 二元归约运算对象，把逐项变换或组合的结果并入当前累加值。 |
| `transform_op` | 输入 | 二元组合运算对象，作用于两个范围中对应位置的元素。 |

### 原型 4 的参数

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
| `initial` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T` | 返回输入值按接口规定运算后的数值结果。 |
| 原型 2 | `T` | 返回输入值按接口规定运算后的数值结果。 |
| 原型 3 | `T` | 返回输入值按接口规定运算后的数值结果。 |
| 原型 4 | `T` | 返回输入值按接口规定运算后的数值结果。 |

## 约束说明

- 使用 C++17
- 该 Host 同步适配接口调用对应的 asc::parallel 前端
- policy 必须包含有效 Stream 和足够的调用方临时存储
- 接口只等待该 Stream
- 由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用 asc::std::terminate
- 提供顺序执行且不进行动态内存分配的重载
- 标准执行策略重载采用顺序执行，并遵循标准允许的求值顺序

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    return asc::std::transform_reduce(input, input + 4, 0, [](int a, int b) { return a + b; }, [](int a) { return a * 2; });
}
```
