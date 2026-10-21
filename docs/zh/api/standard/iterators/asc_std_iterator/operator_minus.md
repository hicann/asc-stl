# `asc::std::operator-`（move_iterator/common_iterator/counted_iterator重载）（函数模板）

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

本页列出移动、公共、计数及反向迭代器的关联非成员差值运算。返回的是两个位置的有符号距离，不移动迭代器、不读取元素；方向和异常规格按下列各形态区分。

## 函数原型

以下为当前公开差值运算的声明摘要；省略仅供SFINAE选择的实现参数，各自条件见原型说明。原型1—7在命名空间中定义；原型8为反向迭代器的隐藏友元。全部可用于C++17和C++20的相应位置。

### 原型1

```cpp
namespace asc::std {
template<class Iter, class Sentinel>
constexpr iter_difference_t<Iter> operator-(const move_sentinel<Sentinel>& sentinel,
    const move_iterator<Iter>& iterator);
}
```

sized_sentinel_for<Sentinel, Iter>须成立。C++17及Device使用SFINAE、Host C++20使用requires；该条件保证C++17声明的底层差值结果与iter_difference_t<Iter>相同。

### 原型2

```cpp
namespace asc::std {
template<class Iter, class Sentinel>
constexpr iter_difference_t<Iter> operator-(const move_iterator<Iter>& iterator,
    const move_sentinel<Sentinel>& sentinel);
}
```

与原型1相同的sized_sentinel_for条件。

### 原型3

```cpp
namespace asc::std {
template<class I1, class S1, class I2, class S2>
constexpr iter_difference_t<I2> operator-(const common_iterator<I1, S1>& left,
    const common_iterator<I2, S2>& right);
}
```

要求sized_sentinel_for<I2,I1>、sized_sentinel_for<S2,I1>与sized_sentinel_for<S1,I2>同时成立；C++17及Device使用SFINAE，Host C++20使用requires。

### 原型4

```cpp
namespace asc::std {
template<class I1, class I2>
[[nodiscard]] constexpr iter_difference_t<I2> operator-(const counted_iterator<I1>& left,
    const counted_iterator<I2>& right);
}
```

两者须表示同一底层序列中可比较的位置，剩余计数的差须可表示。

### 原型5

```cpp
namespace asc::std {
template<class Iter>
constexpr iter_difference_t<Iter> operator-(default_sentinel_t sentinel,
    const counted_iterator<Iter>& value) noexcept;
}
```

value的剩余计数须有效且可由返回差值类型表示。

### 原型6

```cpp
namespace asc::std {
template<class Iter>
constexpr iter_difference_t<Iter> operator-(const counted_iterator<Iter>& value,
    default_sentinel_t sentinel) noexcept;
}
```

value的剩余计数及其负值须可由返回差值类型表示。

### 原型7

```cpp
namespace asc::std {
template<class Left, class Right>
constexpr auto operator-(const move_iterator<Left>& left, const move_iterator<Right>& right)
    -> decltype(left.base() - right.base());
}
```

底层left.base()-right.base()表达式须有效，且两个底层位置属于可求差的同一序列。

### 原型8

```cpp
template<class Iter2>
friend constexpr auto operator-(const reverse_iterator& left, const reverse_iterator<Iter2>& right)
    -> decltype(::asc::std::declval<const Iter2&>() - ::asc::std::declval<const Iter&>());
```

此原型位于reverse_iterator<Iter>的类内，是隐藏友元，须使用left-right的运算符语法。底层反向次序的差值表达式须有效。

## 参数说明

模板参数Iter/Left/Right/I1/I2为底层迭代器类型，Sentinel/S1/S2为与相应迭代器配合的哨兵类型。各选择条件见原型说明。

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 减号左侧的移动哨兵。 |
| `iterator` | 输入 | 减号右侧的移动迭代器。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 减号左侧的移动迭代器。 |
| `sentinel` | 输入 | 减号右侧的移动哨兵。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 保存迭代器或哨兵状态的左侧common_iterator。 |
| `right` | 输入 | 保存迭代器或哨兵状态的右侧common_iterator。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 左侧计数迭代器。 |
| `right` | 输入 | 右侧计数迭代器。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `sentinel` | 输入 | 表示剩余计数为0的结束标记。 |
| `value` | 输入 | 从当前位置计数到结束的计数迭代器。 |

### 原型6的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 左侧计数迭代器。 |
| `sentinel` | 输入 | 右侧结束标记。 |

### 原型7的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 左侧移动迭代器。 |
| `right` | 输入 | 右侧移动迭代器。 |

### 原型8的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 左侧反向迭代器。 |
| `right` | 输入 | 右侧反向迭代器。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `iter_difference_t<Iter>` | sentinel.base() - iterator.base()。 |
| 原型2 | `iter_difference_t<Iter>` | iterator.base() - sentinel.base()。 |
| 原型3 | `iter_difference_t<I2>` | 两侧均为哨兵时返回0；其它状态按各自当前保存位置执行左减右。 |
| 原型4 | `iter_difference_t<I2>` | right.count() - left.count()，即从right位置前进到left位置的有符号距离。 |
| 原型5 | `iter_difference_t<Iter>` | value.count()：结束位置减去当前位置。 |
| 原型6 | `iter_difference_t<Iter>` | -value.count()：当前位置减去结束位置。 |
| 原型7 | `decltype(left.base() - right.base())` | 左侧底层位置减右侧底层位置。 |
| 原型8 | `decltype(right.base() - left.base())` | right.base() - left.base()，与底层正向位置的减法次序相反。 |

## 约束说明

- 两位置必须属于同一底层序列，并满足该原型所列的差值或sized_sentinel_for条件；差值须可表示。
- 计数迭代器用剩余数量计算位置差，不要求访问元素；默认哨兵位于剩余计数0的位置。
- 反向迭代器的差值顺序与基础迭代器相反；隐藏友元使用运算符表达式查找。
- 只有原型5、6显式声明noexcept；不能把其它形态一律看作不抛出。
- 所有适配器均不取得底层存储所有权，存储及位置须在操作期间有效。

## 调用示例

以下Host示例在相同底层数组存活期内检查操作的方向与结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[4] = {2, 4, 6, 8};
    const asc::std::move_iterator<int*> moved_first(values), moved_later(values + 2);
    const asc::std::move_sentinel<int*> moved_end(values + 4);
    const asc::std::counted_iterator<int*> counted_first(values, 4), counted_later(values + 2, 2);
    using common_type = asc::std::common_iterator<int*, const int*>;
    const common_type common_first(values), common_end(static_cast<const int*>(values + 4));
    const asc::std::reverse_iterator<int*> reversed_first(values + 4), reversed_later(values + 2);
    return moved_end - moved_first == 4 && moved_first - moved_end == -4
        && moved_later - moved_first == 2 && counted_later - counted_first == 2
        && asc::std::default_sentinel - counted_first == 4
        && counted_first - asc::std::default_sentinel == -4
        && common_end - common_first == 4 && common_end - common_end == 0
        && reversed_later - reversed_first == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
