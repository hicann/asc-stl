# asc::std::ranges::remove_copy_if_result

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

头文件为 `<asc/std/algorithm>`。保存范围算法返回的输入和输出位置，不拥有底层存储。

## 声明

该名称是对应结果类的别名。

```cpp
namespace asc::std::ranges {
template <class Iterator, class Output>
using remove_copy_if_result = in_out_result<Iterator, Output>;
}  // namespace asc::std::ranges
```

## 参数说明

| 字段 | 含义 |
| --- | --- |
| `in` | 输入位置。 |
| `out` | 输出位置。 |

## 约束说明

满足各字段转换条件时，可从左值复制或从右值移动转换为相应结果类型。字段中的指针和迭代器不延长被引用存储的生命周期；非借用临时范围的输入位置为 `dangling`。

## 调用示例

```cpp
#include <asc/std/algorithm>

bool example()
{
    int source[1]{}, output[1]{};
    asc::std::ranges::remove_copy_if_result<int*, int*> result{source, output};
    return result.in == source && result.out == output;
}
```

## 关联API

- [<asc/std/algorithm>](asc_std_algorithm.md)
