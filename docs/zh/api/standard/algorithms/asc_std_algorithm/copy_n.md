# asc::std::copy_n

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

`asc::std::copy_n`从起始位置复制指定数量的元素；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

```cpp
namespace asc::std {
template <class InputIterator, class Size, class OutputIterator>
constexpr OutputIterator copy_n(InputIterator first, Size count, OutputIterator result);
}  // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示待复制元素个数的类型，通常为整型或迭代器差值类型。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `count` | 输入 | 从first起待复制的元素个数。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `OutputIterator` | 返回最后一个写入元素之后的位置；`count <= 0`时原样返回`result`。 |

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
    int output[16] = {};
    auto result = asc::std::copy_n(values, 4, output);
    return result == output + 4 && output[0] == 1 && output[3] == 4;
}
```

## 关联API

- [`asc::parallel::copy_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_copy_n.md)：使用执行策略提交异步设备操作。
