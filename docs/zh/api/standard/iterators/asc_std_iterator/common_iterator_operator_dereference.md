# asc::std::common_iterator::`operator*`

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

`asc::std::common_iterator::operator*`解引用当前迭代器或有值对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

### 原型1

```cpp
// common_iterator 类内声明节选。
constexpr decltype(auto) operator*();
```

### 原型2

```cpp
// common_iterator 类内声明节选。
template<class I2 = Iter, class = decltype(*declval<const I2&>())>
constexpr decltype(auto) operator*() const;
```

const形式展示C++17及Device选择形式；Host C++20用`requires`检查相同的const解引用表达式。

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 成员选择类型，默认为所属类的`Iter`；须满足本原型的表达式或遍历要求。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `decltype(auto)` | 返回当前迭代器、范围或字符串所指位置的元素引用或代理值。 |
| 原型2 | `decltype(auto)` | 返回当前迭代器、范围或字符串所指位置的元素引用或代理值。 |

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
    const Common copy(iterator);
    return *iterator == 2 && *copy == 2;
}
```

## 关联API

- [`asc::std::common_iterator`](common_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
