# asc::std::find

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

`asc::std::find`在半开区间`[first, last)`中查找首个与`value`相等的元素。找到时返回该元素的位置；不存在目标元素时返回`last`。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Input, class T> Input find(asc::device_policy policy, Input first, Input last, const T& value);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host。

### 原型2

```cpp
namespace asc::std {
template<class InputIterator, class T> [[nodiscard]] constexpr InputIterator find(InputIterator first, InputIterator last, const T& value);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device执行策略，用于指定Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `last` | 输入 | 输入范围的结束迭代器，不包含该位置。 |
| `value` | 输入 | 待查找的值。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `last` | 输入 | 输入范围的结束迭代器，不包含该位置。 |
| `value` | 输入 | 待查找的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `Input` | 返回首个与value相等的元素位置；未找到时返回last。 |
| 原型2 | `InputIterator` | 返回首个与value相等的元素位置；未找到时返回last。 |

## 约束说明

- 使用C++17。
- 该Host同步适配接口调用对应的asc::parallel前端。
- policy必须包含有效Stream和足够的调用方临时存储。
- 接口只等待该Stream。
- 由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用asc::std::terminate。
- 支持当前版本列出的迭代器、哨兵和可调用对象重载。
- 标准执行策略重载采用顺序执行。

## 调用示例

以下示例在整数数组中查找值3，并检查返回位置和元素值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4, 5};
    const auto result = asc::std::find(values, values + 5, 3);
    return result == values + 2 && *result == 3;
}
```

## 关联API

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
