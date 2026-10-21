# asc::std::reduce

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

`asc::std::reduce`从初值开始按当前实现的输入顺序归约范围。

本页说明顺序执行的重载。Device并行提交入口为[`asc::parallel::reduce`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_reduce.md)，其参数、状态返回和完成条件见对应页面。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class InputIterator, class T, class BinaryO> [[nodiscard]] constexpr T reduce(InputIterator first, InputIterator last, T init, BinaryO binary_op);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template<class InputIterator, class T> [[nodiscard]] constexpr T reduce(InputIterator first, InputIterator last, T init);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
template<class InputIterator> [[nodiscard]] constexpr typename iterator_traits<InputIterator>::value_type reduce(InputIterator first, InputIterator last);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 归约初值、中间累加值与返回结果的类型。 |
| `BinaryO` | 逐步合并累加值的二元运算可调用对象类型：接受两个T值并返回可转换为T的结果。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `init` | 输入 | 归约初值，作为逐元素合并的起始累加值；范围为空时原样返回该值。 |
| `binary_op` | 输入 | 二元归约运算对象，按binary_op(当前累加值, 当前元素)逐步合并；省略该参数的重载使用`operator+`。 |

### 原型2的参数

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

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回输入范围按所选二元运算归约后的值。 |
| 原型2 | `T` | 返回输入范围按所选二元运算归约后的值。 |
| 原型3 | `typename iterator_traits<InputIterator>::value_type` | 返回输入范围按所选二元运算归约后的值。 |

## 约束说明

- `[first, last)`须为有效的可读输入范围。
- 当前实现按输入顺序归约，使用`operator+`或`binary_op`更新累加值；运算结果须可赋回结果类型。
- 无初值重载使用输入元素值类型的值初始化对象作为初值；空范围返回初值。

## 调用示例

以下示例从0开始归约1、2、3、4，返回10。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    return asc::std::reduce(input, input + 4, 0);
}
```

## 关联API

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
