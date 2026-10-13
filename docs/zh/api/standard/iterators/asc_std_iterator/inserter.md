# asc::std::inserter

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

`inserter`为调用方容器和插入位置创建输出迭代器；向该迭代器赋值会在当前位置插入并推进位置。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

```cpp
namespace asc::std {
template<class Container> constexpr asc::std::insert_iterator<Container> inserter(Container& container, typename Container::iterator position);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Container` | 接收插入元素的容器类型；须支持该适配器调用的插入操作。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“为调用方容器和插入位置创建输出迭代器”使用的对象引用；被引用对象须在调用期间有效。 |
| `position` | 输入 | 指向本次操作位置的迭代器；所指范围须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::insert_iterator<Container>` | 返回保存目标容器及插入位置的插入迭代器。 |

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>
#include <deque>
#include <functional>
#include <vector>

void example()
{
    ::std::vector<int> values;
    auto output = asc::std::inserter(values, values.begin());
    *output = 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
