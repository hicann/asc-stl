# asc::std::common_iterator::`operator=`

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

`asc::std::common_iterator::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

所属类型：[`asc::std::common_iterator`](common_iterator.md)。

### 原型1

```cpp
// common_iterator 类内声明节选。
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(common_iterator&&) = default;
```

### 原型2

```cpp
// common_iterator 类内声明节选。
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(const common_iterator&) = default;
```

### 原型3

```cpp
// common_iterator 类内声明节选。
template<class I2, class S2,
    enable_if_t<convertible_to<const I2&, Iter> && convertible_to<const S2&, Sent> &&
        assignable_from<Iter&, const I2&> && assignable_from<Sent&, const S2&>, int> = 0>
CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20 common_iterator& operator=(const common_iterator<I2, S2>& other);
```

转换赋值展示C++17及Device形式；Host C++20以`requires`表达相同条件并声明`constexpr`。宏`CANN_ASC_STL_DETAIL_CONSTEXPR_CXX20`在C++20及以上为`constexpr`，在C++17为空。

## 参数说明

| 模板参数 | 描述 |
| --- | --- |
| `I2` | 转换来源的迭代器类型，须能转换构造及赋值为`Iter`。 |
| `S2` | 转换来源的哨兵类型，须能转换构造及赋值为`Sent`。 |

转换赋值的`other`是输入来源对象。前两个特殊赋值成员的来源形参在声明中不具名，分别执行移动或复制赋值。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型3 | `common_iterator<Iter, Sent> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

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
    Common target(asc::std::default_sentinel);
    target = iterator;
    return *target == 2;
}
```

## 关联API

- [`asc::std::common_iterator`](common_iterator.md)
- [本头文件的接口列表](asc_std_iterator.md)
