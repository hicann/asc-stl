# asc::std::counted_iterator::counted_iterator

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

`asc::std::counted_iterator::counted_iterator`按本页所列构造形态初始化`counted_iterator`对象。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::counted_iterator`](counted_iterator.md)。

### 原型1

```cpp
// counted_iterator 类内声明节选。
template<class I2 = Iter, enable_if_t<is_default_constructible_v<I2>, int> = 0>
constexpr counted_iterator();
```

### 原型2

```cpp
// counted_iterator 类内声明节选。
constexpr counted_iterator(Iter value, difference_type count) noexcept(is_nothrow_move_constructible_v<Iter>);
```

### 原型3

```cpp
// counted_iterator 类内声明节选。
template<class I2, enable_if_t<is_convertible_v<const I2&, Iter>, int> = 0>
constexpr counted_iterator(const counted_iterator<I2>& other) noexcept(is_nothrow_constructible_v<Iter, const I2&>);
```

以上为C++17及Device选择形式；Host C++20用`requires`表达对应条件，默认构造为defaulted。

## 参数说明

| 模板参数 | 描述 |
| --- | --- |
| `I2` | 默认构造的选择参数默认为`Iter`；转换构造时为来源底层迭代器类型。 |

| 函数参数 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前底层迭代器；从该位置开始须有`count`个有效元素。 |
| `count` | 输入 | 剩余元素数量，须为非负值；0表示空计数范围。 |
| `other` | 输入 | 转换来源的计数迭代器，同时复制其当前位置和剩余计数。 |

## 返回值说明

无返回值。

## 约束说明

- `Iter`须满足本操作要求的遍历能力；适配器不拥有底层范围。
- `count()`表示从当前位置开始剩余的元素数量；解引用及自增要求剩余数量大于0。
- 位移后的底层位置及对应计数须有效，不得越过实际有效范围。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::counted_iterator<int*> empty;
    asc::std::counted_iterator<int*> direct(values, 2);
    asc::std::counted_iterator<const int*> converted(direct);
    return empty.count() == 0 && converted.count() == 2 &&
           converted.base() == values && *converted == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
