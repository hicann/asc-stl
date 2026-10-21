# asc::std::common_iterator::`operator-`>

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

`asc::std::common_iterator::operator->`返回可用于访问所指对象成员的指针。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

```cpp
// common_iterator 类内声明节选；类模板参数和其余成员由所属类提供。
// C++17及Device选择形式；Host C++20用requires表达相同条件。
template<class I2 = Iter,
    enable_if_t<indirectly_readable<const I2> &&
        (__common_iterator_detail::__ci_has_const_arrow<I2> ||
         is_reference_v<iter_reference_t<I2>> ||
         constructible_from<iter_value_t<I2>, iter_reference_t<I2>>), int> = 0>
constexpr decltype(auto) operator->() const;
```

定义节选中的辅助判定检查底层const迭代器是否可直接提供箭头访问；其他分支从引用取得地址或构造值代理。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 成员选择类型，默认为所属类的`Iter`；须满足本原型的表达式或遍历要求。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `decltype(auto)` | 返回可访问当前所指对象成员的指针。 |

## 约束说明

- `Iter`与`Sent`是不同类型，须满足输入/输出迭代器与哨兵的配合要求；适配器保存其中一种状态。
- 解引用、箭头访问及自增只能作用于当前持有迭代器且操作有效的对象，不能作用于哨兵状态。
- 适配器不拥有底层范围；所指对象须在访问期间保持有效。
- 底层const迭代器须可间接读取，并能通过自身箭头、解引用所得引用或可构造的值代理提供成员访问。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using It = asc::std::counted_iterator<int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common iterator(It(values, 3));
    auto pointer = iterator.operator->();
    return *pointer == 2;
}
```

## 关联API

- [`asc::std::common_iterator`](common_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
