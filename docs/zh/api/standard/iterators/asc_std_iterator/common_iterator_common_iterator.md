# asc::std::common_iterator::common_iterator

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

`asc::std::common_iterator::common_iterator`按本页所列构造形态初始化`common_iterator`对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型1

```cpp
constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>);
```

### 原型2

```cpp
constexpr common_iterator(Iter first) noexcept(is_nothrow_move_constructible_v<Iter>);
```

### 原型3

```cpp
constexpr common_iterator(Sent sentinel) noexcept(is_nothrow_move_constructible_v<Sent>);
```

### 原型4

```cpp
constexpr common_iterator(common_iterator<Iter, Sent>&& other);
```

### 原型5

```cpp
constexpr common_iterator(const common_iterator<Iter, Sent>& other);
```

### 原型6

```cpp
template<class I2, class S2> constexpr common_iterator(const common_iterator<I2, S2>& other) noexcept(is_nothrow_constructible_v<Iter, const I2&>&& is_nothrow_constructible_v<Sent, const S2&>);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 被包装的迭代器；适配器保存其副本，作为当前遍历位置。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 被包装的哨兵；适配器保存其副本，作为范围结束标记。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 移动来源common_iterator；其迭代器与哨兵被移动到新对象，移动后处于有效但未指定状态。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源common_iterator；其迭代器与哨兵被复制到新对象。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `I2` | 来源common_iterator的迭代器类型；须能转换构造为Iter。 |
| `S2` | 来源common_iterator的哨兵类型；须能转换构造为Sent。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源common_iterator（迭代器/哨兵类型可不同）；二者经转换复制到新对象。 |

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
    using It = asc::std::counted_iterator<int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common first(It(values, 2));
    Common last(asc::std::default_sentinel);
    int sum = 0;
    for (; first != last; ++first) sum += *first;
    return sum == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
