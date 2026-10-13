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
template<class InputIter, class Distance, class IntegralDistance, class> constexpr void advance(InputIter& iter, Distance original);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIter` | 被推进的迭代器类型；按其迭代器类别选择步进方式。 |
| `Distance` | 推进距离的类型；可为整数或类整数类型，内部转换为迭代器的difference_type。 |
| `IntegralDistance` | 距离转换为整数后的内部类型，用于重载分派；调用方无需显式指定。 |
| `未命名参数4` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iter` | 输入/输出 | 被原地推进的迭代器；向前移动original步（负值时向后移动，须双向迭代器）。 |
| `original` | 输入 | 推进的步数（元素距离）；正值为前进、负值为后退。 |

## 返回值说明

无返回值。

## 约束说明

- 支持非I/O范围、数组和用户容器。

## 调用示例

以下Host片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

void example()
{
    int values[4] = {1, 2, 3, 4};
    int* iterator = values;
    asc::std::advance(iterator, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
