# asc::std::reverse_iterator

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

`asc::std::reverse_iterator`适配底层迭代器的遍历、计数、逆序、移动或插入方式。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
template<class Iter> class reverse_iterator;
} // namespace asc::std
```

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/vector>
#include <asc/std/forward_list>

bool example()
{
    int values[] = {2, 4};
    asc::std::reverse_iterator<int*> it(values + 2);
    return *it == 4 && *++it == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
