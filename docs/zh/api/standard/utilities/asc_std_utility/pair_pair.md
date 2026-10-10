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

`asc::std::pair::pair` 按本页所列构造形态初始化 `pair` 对象。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

### 原型 1

```cpp
pair(const pair<T1, T2>& other);
```

### 原型 2

```cpp
pair(pair<T1, T2>&& other);
```

### 原型 3

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

### 原型 4

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(const T1& first, const T2& second) noexcept(is_nothrow_copy_constructible_v<T1>&& is_nothrow_copy_constructible_v<T2>);
```

### 原型 5

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair() noexcept(is_nothrow_default_constructible_v<T1>&& is_nothrow_default_constructible_v<T2>);
```

### 原型 6

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(const T1& first, const T2& second) noexcept(is_nothrow_copy_constructible_v<T1>&& is_nothrow_copy_constructible_v<T2>);
```

### 原型 7

```cpp
template<class ...Args1, class ...Args2> constexpr pair(piecewise_construct_t tag, tuple<Args1...> first_args, tuple<Args2...> second_args) noexcept((is_nothrow_constructible_v<T1, Args1...>&& is_nothrow_constructible_v<T2, Args2...>));
```

### 原型 8

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(U1&& first, U2&& second) noexcept(is_nothrow_constructible_v<T1, U1>&& is_nothrow_constructible_v<T2, U2>);
```

### 原型 9

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(const pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, const U1>&& is_nothrow_constructible_v<T2, const U2>);
```

### 原型 10

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(const pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, const U1&>&& is_nothrow_constructible_v<T2, const U2&>);
```

### 原型 11

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, U1>&& is_nothrow_constructible_v<T2, U2>);
```

### 原型 12

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, U1&>&& is_nothrow_constructible_v<T2, U2&>);
```

### 原型 13

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(U1&& first, U2&& second) noexcept(is_nothrow_constructible_v<T1, U1>&& is_nothrow_constructible_v<T2, U2>);
```

### 原型 14

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(const pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, const U1>&& is_nothrow_constructible_v<T2, const U2>);
```

### 原型 15

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(const pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, const U1&>&& is_nothrow_constructible_v<T2, const U2&>);
```

### 原型 16

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(pair<U1, U2>&& other) noexcept(is_nothrow_constructible_v<T1, U1>&& is_nothrow_constructible_v<T2, U2>);
```

### 原型 17

```cpp
template<class U1, class U2, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(pair<U1, U2>& other) noexcept(is_nothrow_constructible_v<T1, U1&>&& is_nothrow_constructible_v<T2, U2&>);
```

### 原型 18

```cpp
template<class UPair, enable_if_t<!is_same_v<remove_cvref_t<UPair>, pair<T1, T2>>, int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr pair(UPair&& other) noexcept(is_nothrow_constructible_v<T1, decltype(::asc::std::Adlget<0>(::asc::std::forward<UPair>(P)))>&& is_nothrow_constructible_v<T2, decltype(::asc::std::Adlget<1>(::asc::std::forward<UPair>(P)))>);
```

### 原型 19

```cpp
template<class UPair, enable_if_t<!is_same_v<remove_cvref_t<UPair>, pair<T1, T2>>, int>, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr pair(UPair&& other) noexcept(is_nothrow_constructible_v<T1, decltype(::asc::std::Adlget<0>(::asc::std::forward<UPair>(P)))>&& is_nothrow_constructible_v<T2, decltype(::asc::std::Adlget<1>(::asc::std::forward<UPair>(P)))>);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `second` | 输入 | 提供“按本页所列构造形态初始化 `pair` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `second` | 输入 | 提供“按本页所列构造形态初始化 `pair` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args1` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Args2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `pair` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `first_args` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入/输出 | 输入范围的起始迭代器或指针。 |
| `second` | 输入/输出 | 提供“按本页所列构造形态初始化 `pair` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 11 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 12 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 13 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入/输出 | 输入范围的起始迭代器或指针。 |
| `second` | 输入/输出 | 提供“按本页所列构造形态初始化 `pair` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 14 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 15 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 16 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 17 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 18 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UPair` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 19 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UPair` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 约束说明

- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::pair<int, int> source(1, 2);
    asc::std::pair<int, int> copy(source);
    (void)copy.first;
}
```
