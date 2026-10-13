# asc::std::prev

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::prev` 返回向后移动指定距离后的迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
template<class InputIter> constexpr InputIter asc::std::prev(InputIter value, typename iterator_traits<InputIter>::difference_type count = 1);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIter` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `count` | 输入 | 参与操作的元素数量。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `InputIter` | 返回按指定距离移动后的位置；是否修改原迭代器以对应原型为准。 |

## 约束说明

- 支持非 I/O 范围、数组和用户容器

## 调用示例

以下 Host 片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::prev(values + 2, 1);
}
```
