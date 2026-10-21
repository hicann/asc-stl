# asc::std::front_insert_iterator::`operator++`

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

`asc::std::front_insert_iterator::operator++`提供输出迭代器的自增形式，操作本身不改变容器或插入位置。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::front_insert_iterator`](front_insert_iterator.md)。

### 原型1

```cpp
// asc::std::front_insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr front_insert_iterator<Container>& operator++() noexcept;
```

### 原型2

```cpp
// asc::std::front_insert_iterator 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr front_insert_iterator<Container> operator++(int unused) noexcept;
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

前置形式返回当前适配器的引用；后置形式按值返回适配器副本。两种形式都不插入元素，也不改变保存的插入位置。

## 约束说明

- 目标容器须支持对应的`push_front(value)`操作；插入迭代器保存容器地址，不拥有容器。
- 容器须在适配器使用期间有效；插入操作还须遵守目标容器自身的迭代器失效规则。
- 解引用与自增用于满足输出迭代器调用形式，本身不插入元素；通过赋值执行插入。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <deque>

bool example()
{
    ::std::deque<int> values;
    asc::std::front_insert_iterator<::std::deque<int>> output(values);
    auto& prefix = ++output;
    auto postfix = output++;
    bool unchanged = &prefix == &output && values.empty();
    *postfix = 7;
    return unchanged && values.size() == 1 && values.front() == 7;
}
```

## 关联API

- [`asc::std::front_insert_iterator`](front_insert_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
