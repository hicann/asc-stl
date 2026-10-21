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

头文件路径为：`<asc/std/array>`、`<asc/std/tuple>`、`<asc/std/utility>`、`<asc/std/variant>`。

`asc::std::get`按编译期索引访问`array`、`tuple`、`pair`的元素，以及`<asc/std/tuple>`导出的`complex<float>`实部或虚部；`tuple`和`pair`还可按类型访问。返回的是原对象中元素的引用，cv限定和值类别随实参传播；被引用对象必须继续存活。`variant`另提供本页列出的8个`get`重载，访问当前活跃候选项；其不匹配失败路径直接触发trap。需要先检查是否匹配时可使用`get_if`。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr T1&& get(tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型2

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr T1& get(tuple<Args...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型3

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr const T1&& get(const tuple<Args...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型4

```cpp
namespace asc::std {
template<class T1, class ...Args> constexpr const T1& get(const tuple<Args...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型5

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型6

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1&& get(pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型7

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型8

```cpp
namespace asc::std {
template<class T1, class T2> constexpr T1& get(pair<T2, T1>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型9

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型10

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1&& get(const pair<T2, T1>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型11

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型12

```cpp
namespace asc::std {
template<class T1, class T2> constexpr const T1& get(const pair<T2, T1>& value) noexcept;
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
template<size_t Index, class ...T> constexpr const tuple_element_t<Index, tuple<T...>>&& get(const tuple<T...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型18

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr const tuple_element_t<Index, tuple<T...>>& get(const tuple<T...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型19

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr tuple_element_t<Index, tuple<T...>>&& get(tuple<T...>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型20

```cpp
namespace asc::std {
template<size_t Index, class ...T> constexpr tuple_element_t<Index, tuple<T...>>& get(tuple<T...>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/tuple>`。

### 原型21

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr const tuple_element_t<Index, pair<T1, T2>>&& get(const pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型22

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr const tuple_element_t<Index, pair<T1, T2>>& get(const pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型23

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr tuple_element_t<Index, pair<T1, T2>>&& get(pair<T1, T2>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型24

```cpp
namespace asc::std {
template<size_t Index, class T1, class T2> constexpr tuple_element_t<Index, pair<T1, T2>>& get(pair<T1, T2>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/utility>`。

### 原型25

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr T&& get(array<T, Size>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型26

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr T& get(array<T, Size>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型27

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr const T&& get(const array<T, Size>&& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型28

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size> constexpr const T& get(const array<T, Size>& value) noexcept;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/array>`。

### 原型29

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(variant<Types...>& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型30

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(const variant<Types...>& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型31

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(variant<Types...>&& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型32

```cpp
namespace asc::std {
template<size_t Index, class... Types>
constexpr decltype(auto) get(const variant<Types...>&& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型33

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(variant<Types...>& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型34

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(const variant<Types...>& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型35

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(variant<Types...>&& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

### 原型36

```cpp
namespace asc::std {
template<class T, class... Types>
constexpr decltype(auto) get(const variant<Types...>&& value);
}
```

此原型对应公共头文件：`<asc/std/variant>`。

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

### 原型29的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标alternative的编译期索引，须小于Types的数量。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的variant对象；返回引用依赖其存储的有效期。 |

### 原型30的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标alternative的编译期索引，须小于Types的数量。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的只读variant对象；返回引用依赖其存储的有效期。 |

### 原型31的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标alternative的编译期索引，须小于Types的数量。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的variant对象；返回引用依赖其存储的有效期。 |

### 原型32的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标alternative的编译期索引，须小于Types的数量。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的只读variant对象；返回引用依赖其存储的有效期。 |

### 原型33的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 须在Types中恰好出现一次的目标alternative类型。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的variant对象；返回引用依赖其存储的有效期。 |

### 原型34的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 须在Types中恰好出现一次的目标alternative类型。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的只读variant对象；返回引用依赖其存储的有效期。 |

### 原型35的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 须在Types中恰好出现一次的目标alternative类型。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的variant对象；返回引用依赖其存储的有效期。 |

### 原型36的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 须在Types中恰好出现一次的目标alternative类型。 |
| `Types` | variant所有候选类型，按声明顺序排列。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 当前必须持有所选alternative的只读variant对象；返回引用依赖其存储的有效期。 |

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
| 原型29 | `variant_alternative_t<Index, variant<Types...>>&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型30 | `const variant_alternative_t<Index, variant<Types...>>&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型31 | `variant_alternative_t<Index, variant<Types...>>&&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型32 | `const variant_alternative_t<Index, variant<Types...>>&&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型33 | `T&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型34 | `const T&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型35 | `T&&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |
| 原型36 | `const T&&`（由decltype(auto)推导） | 返回当前活跃候选的对应引用；活动索引不匹配时触发trap，不抛出bad_variant_access。 |

## 约束说明

- 按索引访问时，`Index`须小于对应对象的元素数量；空array和空tuple没有可访问的元素。pair和complex的有效索引为0、1。
- 按类型访问tuple时，目标类型须至少出现一次；当前实现遇到重复类型时选择第一次出现的位置，这与标准库要求类型唯一的规则不同。按类型访问pair时，目标类型须恰好出现一次，以避免重载歧义。
- 返回引用保留对应原型的const限定和值类别；元素类型本身为引用时，最终类型还遵循引用折叠规则。
- 返回右值引用本身不移动元素；是否移动由调用方对返回引用的后续使用决定。
- 返回引用不延长源对象的生命周期；必须在源对象仍有效时使用，不能返回指向局部对象元素的引用。
- 须包含各原型标注的公共头文件；complex对象自身仍受当前`complex<float>`支持范围限制。
- 原型1—28声明`noexcept`；variant的8个重载没有`noexcept`声明。元素访问不执行元素构造、赋值或比较。

- variant按索引访问要求Index有效且所选类型非void；按类型访问要求目标类型恰好出现一次。当前持有的索引必须匹配，否则实现直接trap；这与标准库抛出bad_variant_access的失败路径不同。需要处理不匹配时可先用holds_alternative或get_if检查。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/array>
#include <asc/std/variant>
#include <asc/std/type_traits>

bool example()
{
    asc::std::array<int, 2> values{{1, 2}};
    auto& first = asc::std::get<0>(values);
    static_assert(asc::std::is_same_v<decltype(first), int&>);
    first = 7;
    asc::std::variant<int, float> selected(3);
    if (!asc::std::holds_alternative<int>(selected)) return false;
    auto& active = asc::std::get<int>(selected);
    static_assert(asc::std::is_same_v<decltype(active), int&>);
    active = 9;
    return &first == &values[0] && values[0] == 7 && asc::std::get<0>(selected) == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
