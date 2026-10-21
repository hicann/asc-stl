# asc::std::reverse_iterator::pointer

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

`asc::std::reverse_iterator::pointer`标识元素指针类型。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

所属类型：[`asc::std::reverse_iterator`](reverse_iterator.md)。

```cpp
// asc::std::reverse_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
using pointer = typename iterator_traits<Iter>::pointer;
```

## 约束说明

- 底层迭代器须支持双向遍历；随机访问成员还要求底层支持对应位移或下标运算。
- 反向迭代器访问`base()`之前的元素，解引用或箭头访问要求该前一位置有效。
- 适配器不拥有底层范围；返回引用或指针的寿命受底层对象约束。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::reverse_iterator<int*>::pointer;
    static_assert(asc::std::is_same_v<selected, int*>);
    return true;
}
```

## 关联API

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
