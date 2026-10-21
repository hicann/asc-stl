# asc::std::next

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

`asc::std::next`返回向前推进指定距离后的迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class InputIterator> constexpr InputIterator next(InputIterator x, asc::std::iter_difference_t<InputIterator> n = 1);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |
| `n` | 输入 | 要移动的距离，默认值为1；负值要求底层迭代器支持有效的双向后退。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `InputIterator` | 返回按指定距离移动后的位置；是否修改原迭代器以对应原型为准。 |

## 约束说明

- `n`是有符号移动距离；负值要求双向迭代器，移动经过的位置必须有效。
- 返回的迭代器不拥有范围，所指对象须在使用期间保持有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto result = asc::std::next(values, 2);
    return result == values + 2 && *result == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
