# asc::std::replace_if

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

`asc::std::replace_if`把满足谓词的元素替换为新值；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator, class Predicate, class T>
constexpr void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Predicate` | 判断元素是否满足条件的可调用对象类型。 |
| `T` | 替换后新值的类型，须可赋给范围内元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `pred` | 输入 | 一元谓词，按调用形式pred(elem)返回bool；返回true的元素被替换为new_value。 |
| `new_value` | 输入 | 替换后的新值，赋给满足谓词的元素。 |

## 返回值说明

无返回值。

## 约束说明

- 使用C++17。
- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::replace_if(values, values + 8, [](int value) { return value % 2 == 0; }, 9);
    const int expected[8] = {9, 3, 9, 1, 7, 9, 5, 9};
    for (int index = 0; index < 8; ++index) { if (values[index] != expected[index]) return false; }
    return true;
}
```

## 关联API

- [`asc::parallel::replace_if`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_replace_if.md)：使用执行策略提交异步设备操作。
