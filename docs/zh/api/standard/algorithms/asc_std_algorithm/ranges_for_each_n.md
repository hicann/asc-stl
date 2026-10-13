# asc::std::ranges::for_each_n

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

`asc::std::ranges::for_each_n`从C++17起对指定数量的元素逐个调用函数，支持投影，返回结束迭代器和调用后的函数对象。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
namespace asc::std::ranges {
for_each_n(first, count, function, projection);
} // namespace asc::std::ranges
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `count` | 输入 | 要处理、保留或跳过的元素数量。 |
| `function` | 输入 | 对输入元素执行操作的可调用对象。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数。 |

## 返回值说明

返回包含处理指定数量元素后的迭代器和调用后函数对象的结果对象。

| 调用形式 | 返回类型 |
| --- | --- |
| 迭代器与数量 | `for_each_n_result<Iterator, Function>` |

## 约束说明

- 起始位置之后必须至少有指定数量的有效元素。
- 函数对象须能接收投影后的元素。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto action = [](int& value) { ++value; };
    auto result = asc::std::ranges::for_each_n(values, 4, action);
    return result.in == values + 4 && values[0] == 2 && values[3] == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
