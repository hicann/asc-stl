# asc::std::get

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

头文件路径为：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`。

`asc::std::get`按编译期索引访问`array`、`tuple`、`pair`的元素，以及`<asc/std/tuple>`导出的`complex<float>`实部或虚部；`tuple`和`pair`还可按唯一类型访问。返回的是原对象中元素的引用，cv限定和值类别随实参传播；被引用对象必须继续存活。`variant`的抛异常`get`重载不在本期交付范围，访问活动备选项请使用`get_if`。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T1, class ...Args> [[nodiscard]] constexpr T1&& get(tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型2

```cpp
namespace asc::std {
template<class T1, class ...Args> [[nodiscard]] constexpr T1& get(tuple<Args...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型3

```cpp
namespace asc::std {
template<class T1, class ...Args> [[nodiscard]] constexpr const T1&& get(const tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型4

```cpp
namespace asc::std {
template<class T1, class ...Args> [[nodiscard]] constexpr const T1& get(const tuple<Args...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型5

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr T1&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型6

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr T1&& get(pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型7

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr T1& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型8

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr T1& get(pair<T2, T1>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型9

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr const T1&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型10

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr const T1&& get(const pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型11

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr const T1& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型12

```cpp
namespace asc::std {
template<class T1, class T2> [[nodiscard]] constexpr const T1& get(const pair<T2, T1>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型13

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr T&& get(complex<T>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型14

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr T& get(complex<T>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型15

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr const T&& get(const complex<T>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型16

```cpp
namespace asc::std {
template<size_t Index, class T> [[nodiscard]] constexpr const T& get(const complex<T>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型17

```cpp
namespace asc::std {
template<size_t Index, class ...T> [[nodiscard]] constexpr const tuple_element_t<Index, tuple<T...>>&& get(const tuple<T...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型18

```cpp
namespace asc::std {
template<size_t Index, class ...T> [[nodiscard]] constexpr const tuple_element_t<Index, tuple<T...>>& get(const tuple<T...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型19

```cpp
namespace asc::std {
template<size_t Index, class ...T> [[nodiscard]] constexpr tuple_element_t<Index, tuple<T...>>&& get(tuple<T...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型20

```cpp
namespace asc::std {
template<size_t Index, class ...T> [[nodiscard]] constexpr tuple_element_t<Index, tuple<T...>>& get(tuple<T...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型21

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr const tuple_element_t<Index, pair<T1, T2>>&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型22

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr const tuple_element_t<Index, pair<T1, T2>>& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型23

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr tuple_element_t<Index, pair<T1, T2>>&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型24

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr tuple_element_t<Index, pair<T1, T2>>& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型25

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr T&& get(array<T, Size>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型26

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr T& get(array<T, Size>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型27

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr const T&& get(const array<T, Size>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型28

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr const T& get(const array<T, Size>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在tuple的元素类型中恰好出现一次。 |
| `Args` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的tuple对象；返回其中类型为T1的元素的右值引用，可被移动。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在tuple的元素类型中恰好出现一次。 |
| `Args` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的tuple对象；返回其中类型为T1的元素的引用。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在tuple的元素类型中恰好出现一次。 |
| `Args` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读tuple对象；返回其中类型为T1的元素的常量右值引用。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在tuple的元素类型中恰好出现一次。 |
| `Args` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读tuple对象；返回其中类型为T1的元素的常量引用。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的pair对象；返回其中类型为T1的成员的右值引用，可被移动。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的pair对象；返回其中类型为T1的成员的右值引用，可被移动。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的pair对象；返回其中类型为T1的成员的引用。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的pair对象；返回其中类型为T1的成员的引用。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读pair对象；返回其中类型为T1的成员的常量右值引用。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读pair对象；返回其中类型为T1的成员的常量右值引用。 |

### 原型11的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读pair对象；返回其中类型为T1的成员的常量引用。 |

### 原型12的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与pair某一成员的类型一致。 |
| `T2` | pair另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读pair对象；返回其中类型为T1的成员的常量引用。 |

### 原型13的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex成员选择，编译期常量；0取实部，1取虚部。 |
| `T` | complex的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待访问实部或虚部的complex对象；Index为0取实部、为1取虚部，返回右值引用。 |

### 原型14的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex成员选择，编译期常量；0取实部，1取虚部。 |
| `T` | complex的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待访问实部或虚部的complex对象；Index为0取实部、为1取虚部。 |

### 原型15的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex成员选择，编译期常量；0取实部，1取虚部。 |
| `T` | complex的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待访问实部或虚部的只读complex对象；Index为0取实部、为1取虚部，返回常量右值引用。 |

### 原型16的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex成员选择，编译期常量；0取实部，1取虚部。 |
| `T` | complex的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待访问实部或虚部的只读complex对象；Index为0取实部、为1取虚部。 |

### 原型17的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < sizeof...(T)。 |
| `T` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读tuple对象；返回第Index个元素的常量右值引用。 |

### 原型18的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < sizeof...(T)。 |
| `T` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读tuple对象；返回第Index个元素的常量引用。 |

### 原型19的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < sizeof...(T)。 |
| `T` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的tuple对象；返回第Index个元素的右值引用，可被移动。 |

### 原型20的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < sizeof...(T)。 |
| `T` | tuple各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的tuple对象；返回第Index个元素的引用。 |

### 原型21的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0取first，1取second。 |
| `T1` | pair第一成员（first）的类型。 |
| `T2` | pair第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读pair对象；Index为0取first、为1取second，返回常量右值引用。 |

### 原型22的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0取first，1取second。 |
| `T1` | pair第一成员（first）的类型。 |
| `T2` | pair第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读pair对象；Index为0取first、为1取second。 |

### 原型23的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0取first，1取second。 |
| `T1` | pair第一成员（first）的类型。 |
| `T2` | pair第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的pair对象；Index为0取first、为1取second，返回右值引用。 |

### 原型24的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0取first，1取second。 |
| `T1` | pair第一成员（first）的类型。 |
| `T2` | pair第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的pair对象；Index为0取first、为1取second。 |

### 原型25的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的数组对象；返回第Index个元素的右值引用，可被移动。 |

### 原型26的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的数组对象；返回第Index个元素的引用。 |

### 原型27的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读数组对象；返回第Index个元素的常量右值引用。 |

### 原型28的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读数组对象；返回第Index个元素的常量引用。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型2 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型3 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型4 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型5 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型6 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型7 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型8 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型9 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型10 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型11 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型12 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型13 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型14 | `T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型15 | `const T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型16 | `const T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型17 | `const tuple_element_t<Index, tuple<T...>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型18 | `const tuple_element_t<Index, tuple<T...>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型19 | `tuple_element_t<Index, tuple<T...>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型20 | `tuple_element_t<Index, tuple<T...>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型21 | `const tuple_element_t<Index, pair<T1, T2>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型22 | `const tuple_element_t<Index, pair<T1, T2>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型23 | `tuple_element_t<Index, pair<T1, T2>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型24 | `tuple_element_t<Index, pair<T1, T2>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型25 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型26 | `T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型27 | `const T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型28 | `const T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 索引必须落在对象元素范围内。
- 按类型访问时该类型必须唯一。
- 返回引用不延长原对象生命周期。
- 各对象类型需包含页面所列的对应公共头。
- 构造、赋值、交换及相关自由函数均不进行动态内存分配。
- 异常规格以对应声明为准；Device侧使用的元素操作须不抛出异常。
- pair的直接自由比较入口为`operator==`和`operator<`；其他关系辅助位于`rel_ops`。
- 支持包括零在内的所有N。
- 成员函数和自由函数均不抛出异常。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/array>

decltype(auto) example()
{
    asc::std::array<int, 2> values{{1, 2}};
    return asc::std::get<0>(values);
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
