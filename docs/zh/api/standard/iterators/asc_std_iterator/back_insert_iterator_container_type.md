# asc::std::back_insert_iterator::container_type

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

`asc::std::back_insert_iterator::container_type`标识容器适配器使用的底层容器类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

所属类型：[`asc::std::back_insert_iterator`](back_insert_iterator.md)。

```cpp
// asc::std::back_insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
using container_type = Container;
```

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host片段用具体迭代器或容器类型实例化本页接口。

```cpp
#include <asc/std/iterator>
#include <deque>
#include <functional>
#include <vector>

#include <asc/std/type_traits>

void example()
{
    using selected = typename asc::std::back_insert_iterator<::std::vector<int>>::container_type;
    static_assert(asc::std::is_same_v<selected, ::std::vector<int>>);
}
```

## 关联API

- [`asc::std::back_insert_iterator`](back_insert_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
