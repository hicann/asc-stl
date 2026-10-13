# asc::std::transform_exclusive_scan

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

`asc::std::transform_exclusive_scan` 先变换输入，再写出排除当前项的前缀归约。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class Input, class Output, class T, class BinaryOperation, class UnaryOperation> Output asc::std::transform_exclusive_scan(asc::device_policy policy, Input first, Input last, Output result, T init, BinaryOperation binary_operation, UnaryOperation unary_operation);
```

该原型适用于 `C++17+`，可用位置为 Host。

### 原型 2

```cpp
template<class InputIterator, class OutputIterator, class T, class BinaryO, class UnaryO> constexpr OutputIterator asc::std::transform_exclusive_scan(InputIterator first, InputIterator last, OutputIterator result, T init, BinaryO b, UnaryO u);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Output` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `T` | 归约初值与前缀结果的类型。 |
| `BinaryOperation` | 前缀归约的二元运算可调用对象类型：接受当前累加值与变换后的元素。 |
| `UnaryOperation` | 一元变换可调用对象类型：对每个输入元素先变换再归约。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略，用于指定 Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入前缀结果的输出迭代器；目标范围须有足够容量。 |
| `init` | 输入 | 前缀归约的初始累加值；作为输出范围首个元素，不并入当前项的变换结果。 |
| `binary_operation` | 输入 | 二元归约运算对象，把 unary_operation 变换后的当前元素并入累加值。 |
| `unary_operation` | 输入 | 一元变换运算对象，先作用于每个输入元素，再参与归约。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `T` | 归约初值与前缀结果的类型。 |
| `BinaryO` | 前缀归约的二元运算可调用对象类型：接受当前累加值与变换后的元素。 |
| `UnaryO` | 一元变换可调用对象类型：对每个输入元素先变换再归约。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |
| `init` | 输入 | 前缀归约的初始累加值；作为输出范围首个元素，不并入当前项的变换结果。 |
| `b` | 输入 | 二元归约运算对象，把 `u` 变换后的当前元素并入累加值。 |
| `u` | 输入 | 一元变换运算对象，先作用于每个输入元素，再参与归约。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `Output` | 返回输出范围中最后一个写入结果之后的位置。 |
| 原型 2 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |

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
    return asc::std::transform_exclusive_scan(input, input + 4, output, 0, [](int a, int b) { return a + b; }, [](int a) { return a * 2; });
}
```
