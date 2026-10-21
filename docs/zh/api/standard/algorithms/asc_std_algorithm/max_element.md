# asc::std::max_element

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::max_element`返回范围内最大元素的位置；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator, class Compare>
[[nodiscard]] constexpr ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare compare);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator>
[[nodiscard]] constexpr ForwardIterator max_element(ForwardIterator first, ForwardIterator last);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Compare` | 定义元素先后顺序的比较对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `ForwardIterator` | 返回范围内最大元素的位置。 |
| 原型2 | `ForwardIterator` | 返回范围内最大元素的位置。 |

## 约束说明

- 空范围返回first（等于last）；否则返回首次出现的最大元素位置。

- 使用C++17。
- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::max_element(values, values + 8);
    return result == values + 7;
}
```

## 关联API

- [`asc::parallel::max_element`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_max_element.md)：使用执行策略提交异步设备操作。
