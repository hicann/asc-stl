# asc::std::advance

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

`asc::std::advance`按给定距离推进迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class InputIter, class Distance>
constexpr void advance(InputIter& __i, Distance __orig_n);
} // namespace asc::std
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `__i` | 输入/输出 | 被推进的迭代器，类型为`InputIter`。 |
| `__orig_n` | 输入 | 类型为`Distance`的元素步数，转换为迭代器的`difference_type`后使用；负值要求支持双向移动。 |

## 返回值说明

无返回值。

## 约束说明

- 推进路径必须位于迭代器允许的有效范围内；仅支持单向前进的迭代器不得使用负距离。
- 随机访问迭代器使用加法推进；双向迭代器按距离符号递增或递减；其他输入迭代器逐次递增。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    int* iterator = values;
    asc::std::advance(iterator, 2);
    return iterator == values + 2 && *iterator == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
