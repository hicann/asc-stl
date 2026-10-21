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

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

### 原型1

```cpp
// common_iterator 类内声明节选。
template<class I2 = Iter, enable_if_t<default_initializable<I2>, int> = 0>
constexpr common_iterator() noexcept(is_nothrow_default_constructible_v<Iter>);
```

### 原型2

```cpp
// common_iterator 类内声明节选。
constexpr common_iterator(Iter value) noexcept(is_nothrow_move_constructible_v<Iter>);
```

### 原型3

```cpp
// common_iterator 类内声明节选。
constexpr common_iterator(Sent value) noexcept(is_nothrow_move_constructible_v<Sent>);
```

### 原型4

```cpp
// common_iterator 类内声明节选。
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(common_iterator&&) = default;
```

### 原型5

```cpp
// common_iterator 类内声明节选。
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator(const common_iterator&) = default;
```

### 原型6

```cpp
// common_iterator 类内声明节选。
template<class I2, class S2, enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent>, int> = 0>
constexpr common_iterator(const common_iterator<I2, S2>& other) noexcept(
    is_nothrow_constructible_v<Iter, const I2&> && is_nothrow_constructible_v<Sent, const S2&>);
```

默认构造和转换构造展示C++17及Device的选择形式；Host C++20使用等价的`requires`条件。`CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20`在C++20及以上为`constexpr`，在C++17为空。

## 参数说明

| 模板参数 | 描述 |
| --- | --- |
| `I2` | 默认构造时默认为`Iter`；转换构造时为来源迭代器类型。 |
| `S2` | 转换来源的哨兵类型，须能转换构造为`Sent`。 |

| 函数参数 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 迭代器或哨兵。构造后只保存相应的一种状态；底层范围须继续保持有效。 |
| `other` | 输入 | 转换来源的公共迭代器，按其当前保存的状态构造。 |

复制与移动构造的来源形参在声明中不具名，分别复制或移动保存的状态。

## 返回值说明

无返回值。

## 约束说明

- `Iter`与`Sent`是不同类型，须满足输入/输出迭代器与哨兵的配合要求；适配器保存其中一种状态。
- 解引用、箭头访问及自增只能作用于当前持有迭代器且操作有效的对象，不能作用于哨兵状态。
- 适配器不拥有底层范围；所指对象须在访问期间保持有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/utility>

bool example()
{
    int values[] = {2, 4};
    using It = asc::std::counted_iterator<int*>;
    using ConstIt = asc::std::counted_iterator<const int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common empty;
    Common direct(It(values, 2));
    Common last(asc::std::default_sentinel);
    Common copied(direct);
    Common moved(asc::std::move(copied));
    asc::std::common_iterator<ConstIt, asc::std::default_sentinel_t> converted(direct);
    return empty == last && *moved == 2 && *converted == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
