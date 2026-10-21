# asc::std::copy_backward

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

`asc::std::copy_backward`从尾部向前复制范围，以支持按规定方向重叠的区间；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

```cpp
namespace asc::std {
template <class BidirectionalIterator1, class BidirectionalIterator2>
constexpr BidirectionalIterator2 copy_backward(
    BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result);
}  // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BidirectionalIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `BidirectionalIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 输出范围的末端（排他）；向其之前依次写入输入元素，前方须有足够容量。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `BidirectionalIterator2` | 返回输出范围中已写入部分的起始位置。 |

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto result = asc::std::copy_backward(values, values + 8, output + 8);
    return result == output && output[0] == 1 && output[7] == 8;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
