# asc::std::iter_swap

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

头文件路径为：`<asc/std/algorithm>`、`<asc/std/iterator>`。

`asc::std::iter_swap`交换两个迭代器所指向的元素；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
constexpr auto iter_swap(ForwardIterator1 left, ForwardIterator2 right) noexcept(
    noexcept(swap(*left, *right))) -> decltype(void(swap(*left, *right)));
}  // namespace asc::std
```

此原型对应头文件：`<asc/std/algorithm>`、`<asc/std/iterator>`。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |
| `b` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

## 返回值说明

无返回值。

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载。
- 支持非I/O范围、数组和用户容器。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {8, 3, 6, 1, 7, 2, 5, 4};
    asc::std::iter_swap(values, values + 1);
    return values[0] == 3 && values[1] == 8 && values[2] == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
