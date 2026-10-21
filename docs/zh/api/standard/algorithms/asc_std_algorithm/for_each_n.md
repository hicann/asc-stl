# asc::std::for_each_n

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

`asc::std::for_each_n`从起始位置起对指定数量的元素调用函数对象；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class InputIterator, class Size, class Function>
constexpr InputIterator for_each_n(InputIterator first, Size orig_n, Function f);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示待处理元素个数的类型，通常为整型或迭代器差值类型。 |
| `Function` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `orig_n` | 输入 | 从first起待应用函数对象的元素个数。 |
| `f` | 输入 | 可调用对象，从first起对每个元素以调用形式f(elem)调用一次。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `InputIterator` | 返回处理指定数量元素后的迭代器或结果对象。 |

## 约束说明

- 使用C++17。
- 支持当前版本列出的迭代器、哨兵和可调用对象重载。
- 标准执行策略重载采用顺序执行。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto action = [](int& value) { ++value; };
    auto result = asc::std::for_each_n(values, 4, action);
    return result == values + 4 && values[0] == 2 && values[3] == 5 && values[4] == 5;
}
```

## 关联API

- [`asc::parallel::for_each_n`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_for_each_n.md)：使用执行策略提交异步设备操作。
