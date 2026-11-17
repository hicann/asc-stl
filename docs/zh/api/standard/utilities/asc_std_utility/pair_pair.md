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

以下为`pair<T1, T2>`类内的**调用形态摘要**，省略实现选择器。各形态只在对应元素可构造或可赋值时参与；默认/值构造是否explicit按元素的隐式转换能力分层，不能把摘要合并为无条件重载定义。

```cpp
template<class U1 = T1, class U2 = T2> constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

```cpp
template<class U1 = T1, class U2 = T2> explicit constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

```cpp
pair(const pair& other) = default;
```

```cpp
pair(pair&& other) = default;
```

```cpp
template<class U1 = T1, class U2 = T2> constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class U1, class U2> explicit constexpr pair(U1&& left, U2&& right) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class U1, class U2> constexpr pair(pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, U1&>&& is_nothrow_constructible_v<T2, U2&>);
```

```cpp
template<class U1, class U2> constexpr pair(const pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, const U1&&>&& is_nothrow_constructible_v<T2, const U2&&>);
```

```cpp
template<class PairLike> constexpr pair(PairLike&& other);
```

```cpp
template<class U1, class U2> constexpr pair(const pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, const U1&>&& is_nothrow_constructible_v<T2, const U2&>);
```

```cpp
template<class U1, class U2> constexpr pair(pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, U1&&>&& is_nothrow_constructible_v<T2, U2&&>);
```

```cpp
template<class... Args1, class... Args2> constexpr pair(piecewise_construct_t, tuple<Args1...> left, tuple<Args2...> right) noexcept(is_nothrow_constructible_v<T1, Args1...>&& is_nothrow_constructible_v<T2, Args2...>);
```

## 参数说明

摘要省略的选择参数已转为本页公开参与条件，调用方按普通实参调用。

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

- pair-like形态省略了计算出的noexcept表达式：相应元素的获取与构造均不抛出时，构造不抛出；其余形态的异常说明见摘要原型。

- 默认构造要求两个元素可默认构造；两者均可隐式默认构造时采用隐式形式，否则显式。双值构造要求逐元素可构造，两个来源均可隐式转换时不带explicit。pair-like形态要求有两个可通过get访问的元素、且来源不是pair特化；piecewise_construct将两组tuple实参分别用于first和second。

- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。

## 调用示例

pair-like重载先判断来源是否为tuple-like，再检查元素类型。`int`等非tuple-like来源不参与该重载；`is_constructible_v<pair<int, int>, int>`为false，不会产生元素访问错误。复制pair或将pair引用保存在tuple中仍选择对应的普通构造函数，张量切片辅助逻辑依赖这一行为。

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
