# asc::std::reverse_iterator::reverse_iterator

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

`asc::std::reverse_iterator::reverse_iterator`按本页所列构造形态初始化`reverse_iterator`对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型1

```cpp
constexpr reverse_iterator(Iter first) noexcept(is_nothrow_copy_constructible_v<Iter>);
```

### 原型2

```cpp
template<class It2> constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<It2>);
```

### 原型3

```cpp
template<class U> constexpr reverse_iterator(const reverse_iterator<U>& other) noexcept(Noexceptreviterconvertible<U, Iter>);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `It2` | 来源迭代器的类型；须满足到当前底层迭代器类型的转换条件。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 来源迭代器类型；须满足当前适配器的转换或赋值条件。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- 使用调用方提供的迭代器或容器。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::reverse_iterator<int*> iterator(values + 2);
    return *iterator == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
