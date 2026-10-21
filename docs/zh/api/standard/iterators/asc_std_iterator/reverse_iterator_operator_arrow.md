# asc::std::reverse_iterator::`operator-`>

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

`asc::std::reverse_iterator::operator->`返回可用于访问所指对象成员的指针。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::reverse_iterator`](reverse_iterator.md)。

```cpp
// reverse_iterator 类内声明节选；类模板参数和其余成员由所属类提供。
template<class It = Iter,
    enable_if_t<__reverse_iterator_detail::__has_const_arrow<It>, int> = 0>
constexpr pointer operator->() const;
```

定义节选中的辅助判定要求底层是指针或提供可在const对象上调用的箭头运算符；返回的地址对应`base()`之前的元素。

## 参数说明

| 模板参数 | 描述 |
| --- | --- |
| `It` | 底层迭代器的选择类型，默认为`Iter`；须是指针或支持const箭头访问。 |

无函数参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `pointer` | 返回可访问当前所指对象成员的指针。 |

## 约束说明

- 底层迭代器须支持双向遍历；随机访问成员还要求底层支持对应位移或下标运算。
- 反向迭代器访问`base()`之前的元素，解引用或箭头访问要求该前一位置有效。
- 适配器不拥有底层范围；返回引用或指针的寿命受底层对象约束。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::reverse_iterator<int*> iterator(values + 4);
    auto pointer = iterator.operator->();
    return pointer == values + 3 && *pointer == 8;
}
```

## 关联API

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
