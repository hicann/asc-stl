# asc::std::generate_n

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

`asc::std::generate_n`调用生成器指定次数并依次写入结果；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class OutputIterator, class Size, class Generator>
constexpr OutputIterator generate_n(OutputIterator first, Size orig_n, Generator gen);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `Size` | 表示待生成元素个数的类型，通常为整型或迭代器差值类型。 |
| `Generator` | 生成器类型；调用形式为gen()，返回值须可赋给目标元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 目标输出范围的起始迭代器或指针，从该位置起写入结果。 |
| `orig_n` | 输入 | 从first起待调用生成器并写入的元素个数。 |
| `gen` | 输入 | 生成器对象，依次调用orig_n次，返回值写入对应元素。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `OutputIterator` | 返回输出范围中最后一个写入元素之后的位置。 |

## 约束说明

- 使用C++17。
- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto generator = []() { return 7; };
    auto result = asc::std::generate_n(values, 4, generator);
    return result == values + 4 && values[0] == 7 && values[3] == 7 && values[4] == 5;
}
```

## 关联API

- [`asc::parallel::generate_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_generate_n.md)：使用执行策略提交异步设备操作。
