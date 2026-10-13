# asc::std::pair::operator=

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

`asc::std::pair::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

### 原型 1

```cpp
pair<T1, T2>& asc::std::pair::operator=(const pair<T1, T2>& other);
```

### 原型 2

```cpp
pair<T1, T2>& asc::std::pair::operator=(pair<T1, T2>&& other);
```

### 原型 3

```cpp
template<class U1, class U2, enable_if_t<is_assignable_v<T1&, U1>, int>, enable_if_t<is_assignable_v<T2&, U2>, int>> constexpr pair<T1, T2>& asc::std::pair::operator=(pair<U1, U2>&& other) noexcept(is_nothrow_assignable_v<T1&, U1>&& is_nothrow_assignable_v<T2&, U2>);
```

### 原型 4

```cpp
template<class U1, class U2, enable_if_t<is_assignable_v<T1&, const U1&>, int>, enable_if_t<is_assignable_v<T2&, const U2&>, int>> constexpr pair<T1, T2>& asc::std::pair::operator=(const pair<U1, U2>& other) noexcept(is_nothrow_assignable_v<T1&, const U1&>&& is_nothrow_assignable_v<T2&, const U2&>);
```

### 原型 5

```cpp
template<class U1, class U2, enable_if_t<is_assignable_v<const T1&, U1>, int>, enable_if_t<is_assignable_v<const T2&, U2>, int>> constexpr const pair<T1, T2>& asc::std::pair::operator=(pair<U1, U2>&& other) const noexcept(is_nothrow_assignable_v<const T1&, U1>&& is_nothrow_assignable_v<const T2&, U2>);
```

### 原型 6

```cpp
template<class U1, class U2, enable_if_t<is_assignable_v<const T1&, const U1&>, int>, enable_if_t<is_assignable_v<const T2&, const U2&>, int>> constexpr const pair<T1, T2>& asc::std::pair::operator=(const pair<U1, U2>& other) const noexcept(is_nothrow_assignable_v<const T1&, const U1&>&& is_nothrow_assignable_v<const T2&, const U2&>);
```

### 原型 7

```cpp
template<class PairLike, enable_if_t<__tuple_like_ext<remove_cvref_t<PairLike>> && !__is_pair<remove_cvref_t<PairLike>>::value && is_assignable_v<T1&, decltype(::asc::std::__adl_get<0>(::asc::std::declval<PairLike>()))> && is_assignable_v<T2&, decltype(::asc::std::__adl_get<1>(::asc::std::declval<PairLike>()))>, int>> constexpr pair<T1, T2>& asc::std::pair::operator=(PairLike&& other);
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
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `PairLike` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 3 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 4 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 5 | `const pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 6 | `const pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 7 | `pair<T1, T2> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- pair 操作不抛出异常
- 关系运算符均为显式提供

## 调用示例

以下 Host 片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::pair<int, int> left(1, 2), right(3, 4);
    left = right;
}
```
