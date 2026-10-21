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

所属类型：[`asc::std::reverse_iterator`](reverse_iterator.md)。

### 原型1

```cpp
// reverse_iterator 类内声明节选。
constexpr explicit reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>);
```

### 原型2

```cpp
// reverse_iterator 类内声明节选。
template<class It = Iter, enable_if_t<is_default_constructible_v<It>, int> = 0>
constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<It>);
```

### 原型3

```cpp
// reverse_iterator 类内声明节选。
template<class Other, enable_if_t<!is_same_v<Other, Iter> && is_convertible_v<const Other&, Iter>, int> = 0>
constexpr reverse_iterator(const reverse_iterator<Other>& other)
    noexcept(noexcept(Iter(declval<const Other&>())));
```

转换构造的异常条件使用公开表达式等价表示底层转换是否抛出异常。

## 参数说明

| 模板参数 | 描述 |
| --- | --- |
| `It` | 默认构造的选择类型，默认为所属类的`Iter`，须可默认构造。 |
| `Other` | 转换来源适配器的底层迭代器类型，须满足原型的转换条件。 |

| 函数参数 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 包装的底层迭代器；保存的迭代器须在后续操作中保持有效。 |
| `other` | 输入 | 转换来源适配器，从其底层迭代器构造本对象。 |

## 返回值说明

无返回值。

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
    int values[] = {2, 4};
    asc::std::reverse_iterator<int*> empty;
    asc::std::reverse_iterator<int*> direct(values + 2);
    asc::std::reverse_iterator<const int*> converted(direct);
    static_assert(!asc::std::is_convertible_v<int*, asc::std::reverse_iterator<int*>>);
    return empty.base() == nullptr && converted.base() == values + 2 && *converted == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
