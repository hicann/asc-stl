# asc::std::common_iterator::`operator++`

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

`asc::std::common_iterator::operator++`把当前迭代器或计数值推进一步。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

### 原型1

```cpp
// asc::std::common_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr common_iterator<Iter, Sent>& operator++();
```

### 原型2

```cpp
// asc::std::common_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr decltype(auto) operator++(int unused);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `unused` | 输入 | 用于区分后置自增或后置自减形式的占位参数；调用时写作整数0。 |

## 返回值说明

前置形式返回递增后当前适配器的引用。后置形式在底层满足前向迭代器要求时返回递增前的适配器副本；其他情况下可能返回保存旧值的代理或底层后置递增结果。

## 约束说明

- `Iter`与`Sent`是不同类型，须满足输入/输出迭代器与哨兵的配合要求；适配器保存其中一种状态。
- 解引用、箭头访问及自增只能作用于当前持有迭代器且操作有效的对象，不能作用于哨兵状态。
- 适配器不拥有底层范围；所指对象须在访问期间保持有效。

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
    auto old = iterator++;
    return *old == 2 && *iterator == 4;
}
```

## 关联API

- [`asc::std::common_iterator`](common_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
