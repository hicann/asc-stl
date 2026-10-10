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

`asc::std::advance` 按给定距离推进迭代器。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
template<class InputIter, class Distance, class IntegralDistance, class> constexpr void asc::std::advance(InputIter& iter, Distance original);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIter` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Distance` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `IntegralDistance` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数4` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iter` | 输入/输出 | 提供“按给定距离推进迭代器”使用的对象引用；被引用对象须在调用期间有效。 |
| `original` | 输入 | 提供“按给定距离推进迭代器”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

无返回值。

## 约束说明

- 支持非 I/O 范围、数组和用户容器

## 调用示例

以下 Host 片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

void example()
{
    int values[4] = {1, 2, 3, 4};
    int* iterator = values;
    asc::std::advance(iterator, 2);
}
```
