# asc::std::pair::pair

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

头文件路径为：`<asc/std/utility>`。

`asc::std::pair::pair`按本页所列构造形态初始化`pair`对象。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

以下为`asc::std::pair<T1, T2>`的类内构造声明；`T1`、`T2`来自所属类模板。

### 原型1

```cpp
template<class U1 = T1, class U2 = T2, enable_if_t<is_default_constructible_v<U1> && is_default_constructible_v<U2> && __is_implicitly_default_constructible<U1>::value && __is_implicitly_default_constructible<U2>::value, int>> constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

### 原型2

```cpp
template<class U1 = T1, class U2 = T2, enable_if_t<is_default_constructible_v<U1> && is_default_constructible_v<U2> && !(__is_implicitly_default_constructible<U1>::value && __is_implicitly_default_constructible<U2>::value), long>> explicit constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

### 原型3

```cpp
pair(const pair<T1, T2>& other);
```

### 原型4

```cpp
pair(pair<T1, T2>&& other);
```

### 原型5

```cpp
template<class U1 = T1, class U2 = T2, enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&> && is_convertible_v<U1&&, T1> && is_convertible_v<U2&&, T2>, int>> constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

### 原型6

```cpp
template<class U1, class U2, enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&> && !(is_convertible_v<U1&&, T1> && is_convertible_v<U2&&, T2>), long>> explicit constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

### 原型7

```cpp
template<class U1, class U2, enable_if_t<is_constructible_v<T1, U1&> && is_constructible_v<T2, U2&>, int>> constexpr pair(pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, U1&>&& is_nothrow_constructible_v<T2, U2&>);
```

### 原型8

```cpp
template<class U1, class U2, enable_if_t<is_constructible_v<T1, const U1&&> && is_constructible_v<T2, const U2&&>, int>> constexpr pair(const pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, const U1&&>&& is_nothrow_constructible_v<T2, const U2&&>);
```

### 原型9

```cpp
template<class PairLike, enable_if_t<__tuple_like_ext<remove_cvref_t<PairLike>> && !__is_pair<remove_cvref_t<PairLike>>::value && is_constructible_v<T1, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))> && is_constructible_v<T2, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>, int>> constexpr pair(PairLike&& other) noexcept(is_nothrow_constructible_v<T1, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))>&& is_nothrow_constructible_v<T2, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>);
```

### 原型10

```cpp
template<class U1, class U2, enable_if_t<is_constructible_v<T1, const U1&> && is_constructible_v<T2, const U2&>, int>> constexpr pair(const pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, const U1&>&& is_nothrow_constructible_v<T2, const U2&>);
```

### 原型11

```cpp
template<class U1, class U2, enable_if_t<is_constructible_v<T1, U1&&> && is_constructible_v<T2, U2&&>, int>> constexpr pair(pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

### 原型12

```cpp
template<class... Args1, class... Args2> constexpr pair(piecewise_construct_t, tuple<Args1...> left, tuple<Args2...> right) noexcept(is_nothrow_constructible_v<T1, Args1...>&& is_nothrow_constructible_v<T2, Args2...>);
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | first构造来源的类型；默认使用T1，实际调用可由转发引用推导。 |
| `U2` | second构造来源的类型；默认使用T2，实际调用可由转发引用推导。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | first构造来源的类型；默认使用T1，实际调用可由转发引用推导。 |
| `U2` | second构造来源的类型；默认使用T2，实际调用可由转发引用推导。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 用于初始化第一个元素的值；被引用对象须在调用期间有效。 |
| `right` | 输入/输出 | 用于初始化第二个元素的值；被引用对象须在调用期间有效。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 用于初始化第一个元素的值；被引用对象须在调用期间有效。 |
| `right` | 输入/输出 | 用于初始化第二个元素的值；被引用对象须在调用期间有效。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `PairLike` | 提供两个元素及相应get访问的pair-like类型，两个元素须可用于对应构造或赋值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型11的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 来源pair的first元素或首个构造实参的类型。 |
| `U2` | 来源pair的second元素或第二个构造实参的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型12的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args1` | 转发给第一个元素构造的实参类型列表。 |
| `Args2` | 转发给第二个元素构造的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 转发给第一个元素构造的实参元组。 |
| `right` | 输入 | 转发给第二个元素构造的实参元组。 |

## 返回值说明

无返回值。

## 约束说明

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/utility>
#include <asc/std/tuple>

bool example()
{
    asc::std::pair<int, int> zero;
    asc::std::pair<int, int> values(2, 4);
    auto copy = values;
    auto moved = asc::std::move(copy);
    asc::std::pair<int, int> piecewise(asc::std::piecewise_construct,
        asc::std::make_tuple(3), asc::std::make_tuple(5));
    return zero.first == 0 && moved.first == 2 && moved.second == 4 && piecewise.first == 3 && piecewise.second == 5;
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
