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

`asc::std::get` 按编译期索引访问 `array`、`tuple`、`pair` 的元素，以及 `<asc/std/tuple>` 导出的 `complex<float>` 实部或虚部；`tuple` 和 `pair` 还可按唯一类型访问。返回的是原对象中元素的引用，cv 限定和值类别随实参传播；被引用对象必须继续存活。`variant` 的抛异常 `get` 重载不在本期交付范围，访问活动备选项请使用 `get_if`。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型 1

```cpp
template<class T1, class ...Args> [[nodiscard]] constexpr T1&& asc::std::get(tuple<Args...>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 2

```cpp
template<class T1, class ...Args> [[nodiscard]] constexpr T1& asc::std::get(tuple<Args...>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 3

```cpp
template<class T1, class ...Args> [[nodiscard]] constexpr const T1&& asc::std::get(const tuple<Args...>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 4

```cpp
template<class T1, class ...Args> [[nodiscard]] constexpr const T1& asc::std::get(const tuple<Args...>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 5

```cpp
template<class T1, class T2> [[nodiscard]] constexpr T1&& asc::std::get(pair<T1, T2>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 6

```cpp
template<class T1, class T2> [[nodiscard]] constexpr T1&& asc::std::get(pair<T2, T1>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 7

```cpp
template<class T1, class T2> [[nodiscard]] constexpr T1& asc::std::get(pair<T1, T2>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 8

```cpp
template<class T1, class T2> [[nodiscard]] constexpr T1& asc::std::get(pair<T2, T1>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 9

```cpp
template<class T1, class T2> [[nodiscard]] constexpr const T1&& asc::std::get(const pair<T1, T2>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 10

```cpp
template<class T1, class T2> [[nodiscard]] constexpr const T1&& asc::std::get(const pair<T2, T1>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 11

```cpp
template<class T1, class T2> [[nodiscard]] constexpr const T1& asc::std::get(const pair<T1, T2>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 12

```cpp
template<class T1, class T2> [[nodiscard]] constexpr const T1& asc::std::get(const pair<T2, T1>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 13

```cpp
template<size_t Index, class T> [[nodiscard]] constexpr T&& asc::std::get(complex<T>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 14

```cpp
template<size_t Index, class T> [[nodiscard]] constexpr T& asc::std::get(complex<T>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 15

```cpp
template<size_t Index, class T> [[nodiscard]] constexpr const T&& asc::std::get(const complex<T>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 16

```cpp
template<size_t Index, class T> [[nodiscard]] constexpr const T& asc::std::get(const complex<T>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 17

```cpp
template<size_t Index, class ...T> [[nodiscard]] constexpr const tuple_element_t<Index, tuple<T...>>&& asc::std::get(const tuple<T...>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 18

```cpp
template<size_t Index, class ...T> [[nodiscard]] constexpr const tuple_element_t<Index, tuple<T...>>& asc::std::get(const tuple<T...>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 19

```cpp
template<size_t Index, class ...T> [[nodiscard]] constexpr tuple_element_t<Index, tuple<T...>>&& asc::std::get(tuple<T...>&& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 20

```cpp
template<size_t Index, class ...T> [[nodiscard]] constexpr tuple_element_t<Index, tuple<T...>>& asc::std::get(tuple<T...>& value) noexcept;
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型 21

```cpp
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr const tuple_element_t<Index, pair<T1, T2>>&& asc::std::get(const pair<T1, T2>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 22

```cpp
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr const tuple_element_t<Index, pair<T1, T2>>& asc::std::get(const pair<T1, T2>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 23

```cpp
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr tuple_element_t<Index, pair<T1, T2>>&& asc::std::get(pair<T1, T2>&& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 24

```cpp
template<size_t Index, class T1, class T2> [[nodiscard]] constexpr tuple_element_t<Index, pair<T1, T2>>& asc::std::get(pair<T1, T2>& value) noexcept;
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 25

```cpp
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr T&& asc::std::get(array<T, Size>&& value) noexcept;
```

此原型对应头文件：`<asc/std/array>`。

### 原型 26

```cpp
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr T& asc::std::get(array<T, Size>& value) noexcept;
```

此原型对应头文件：`<asc/std/array>`。

### 原型 27

```cpp
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr const T&& asc::std::get(const array<T, Size>&& value) noexcept;
```

此原型对应头文件：`<asc/std/array>`。

### 原型 28

```cpp
template<size_t Index, class T, size_t Size> [[nodiscard]] constexpr const T& asc::std::get(const array<T, Size>& value) noexcept;
```

此原型对应头文件：`<asc/std/array>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在 tuple 的元素类型中恰好出现一次。 |
| `Args` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 tuple 对象；返回其中类型为 T1 的元素的右值引用，可被移动。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在 tuple 的元素类型中恰好出现一次。 |
| `Args` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 tuple 对象；返回其中类型为 T1 的元素的引用。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在 tuple 的元素类型中恰好出现一次。 |
| `Args` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 tuple 对象；返回其中类型为 T1 的元素的常量右值引用。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标元素类型；须在 tuple 的元素类型中恰好出现一次。 |
| `Args` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 tuple 对象；返回其中类型为 T1 的元素的常量引用。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 pair 对象；返回其中类型为 T1 的成员的右值引用，可被移动。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 pair 对象；返回其中类型为 T1 的成员的右值引用，可被移动。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 pair 对象；返回其中类型为 T1 的成员的引用。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按类型访问的 pair 对象；返回其中类型为 T1 的成员的引用。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 pair 对象；返回其中类型为 T1 的成员的常量右值引用。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 pair 对象；返回其中类型为 T1 的成员的常量右值引用。 |

### 原型 11 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 pair 对象；返回其中类型为 T1 的成员的常量引用。 |

### 原型 12 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 按类型访问的目标成员类型；须与 pair 某一成员的类型一致。 |
| `T2` | pair 另一成员的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按类型访问的只读 pair 对象；返回其中类型为 T1 的成员的常量引用。 |

### 原型 13 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex 成员选择，编译期常量；0 取实部，1 取虚部。 |
| `T` | complex 的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待访问实部或虚部的 complex 对象；Index 为 0 取实部、为 1 取虚部，返回右值引用。 |

### 原型 14 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex 成员选择，编译期常量；0 取实部，1 取虚部。 |
| `T` | complex 的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待访问实部或虚部的 complex 对象；Index 为 0 取实部、为 1 取虚部。 |

### 原型 15 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex 成员选择，编译期常量；0 取实部，1 取虚部。 |
| `T` | complex 的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待访问实部或虚部的只读 complex 对象；Index 为 0 取实部、为 1 取虚部，返回常量右值引用。 |

### 原型 16 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | complex 成员选择，编译期常量；0 取实部，1 取虚部。 |
| `T` | complex 的标量类型，即实部与虚部的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待访问实部或虚部的只读 complex 对象；Index 为 0 取实部、为 1 取虚部。 |

### 原型 17 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < sizeof...(T)。 |
| `T` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读 tuple 对象；返回第 Index 个元素的常量右值引用。 |

### 原型 18 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < sizeof...(T)。 |
| `T` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读 tuple 对象；返回第 Index 个元素的常量引用。 |

### 原型 19 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < sizeof...(T)。 |
| `T` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的 tuple 对象；返回第 Index 个元素的右值引用，可被移动。 |

### 原型 20 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < sizeof...(T)。 |
| `T` | tuple 各元素的类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的 tuple 对象；返回第 Index 个元素的引用。 |

### 原型 21 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0 取 first，1 取 second。 |
| `T1` | pair 第一成员（first）的类型。 |
| `T2` | pair 第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读 pair 对象；Index 为 0 取 first、为 1 取 second，返回常量右值引用。 |

### 原型 22 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0 取 first，1 取 second。 |
| `T1` | pair 第一成员（first）的类型。 |
| `T2` | pair 第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读 pair 对象；Index 为 0 取 first、为 1 取 second。 |

### 原型 23 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0 取 first，1 取 second。 |
| `T1` | pair 第一成员（first）的类型。 |
| `T2` | pair 第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的 pair 对象；Index 为 0 取 first、为 1 取 second，返回右值引用。 |

### 原型 24 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标成员下标，编译期常量；0 取 first，1 取 second。 |
| `T1` | pair 第一成员（first）的类型。 |
| `T2` | pair 第二成员（second）的类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的 pair 对象；Index 为 0 取 first、为 1 取 second。 |

### 原型 25 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的数组对象；返回第 Index 个元素的右值引用，可被移动。 |

### 原型 26 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待按下标访问的数组对象；返回第 Index 个元素的引用。 |

### 原型 27 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读数组对象；返回第 Index 个元素的常量右值引用。 |

### 原型 28 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标元素下标，编译期常量；须满足 Index < Size。 |
| `T` | 数组元素类型。 |
| `Size` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按下标访问的只读数组对象；返回第 Index 个元素的常量引用。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 2 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 3 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 4 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 5 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 6 | `T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 7 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 8 | `T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 9 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 10 | `const T1 &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 11 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 12 | `const T1 &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 13 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 14 | `T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 15 | `const T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 16 | `const T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 17 | `const tuple_element_t<Index, tuple<T...>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 18 | `const tuple_element_t<Index, tuple<T...>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 19 | `tuple_element_t<Index, tuple<T...>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 20 | `tuple_element_t<Index, tuple<T...>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 21 | `const tuple_element_t<Index, pair<T1, T2>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 22 | `const tuple_element_t<Index, pair<T1, T2>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 23 | `tuple_element_t<Index, pair<T1, T2>> &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 24 | `tuple_element_t<Index, pair<T1, T2>> &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 25 | `T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 26 | `T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 27 | `const T &&` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |
| 原型 28 | `const T &` | 返回对象引用；被引用对象须在引用使用期间保持有效。 |

## 约束说明

- 索引必须落在对象元素范围内
- 按类型访问时该类型必须唯一
- 返回引用不延长原对象生命周期
- 各对象类型需包含页面所列的对应公共头
- 构造、赋值、交换及相关自由函数均不进行动态内存分配
- pair 操作不抛出异常
- 关系运算符均为显式提供
- 支持包括零在内的所有 N
- 成员函数和自由函数均不抛出异常

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
