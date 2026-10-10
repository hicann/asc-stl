# asc::std::tuple::operator=

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

头文件路径为：`<asc/std/tuple>`。

`asc::std::tuple::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

### 原型 1

```cpp
tuple<Types...>& asc::std::tuple::operator=(const tuple<Types...>& other);
```

### 原型 2

```cpp
tuple<Types...>& asc::std::tuple::operator=(tuple<Types...>&& other);
```

### 原型 3

```cpp
template<Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr const tuple<Types...>& asc::std::tuple::operator=(const tuple<Types...>& other) const noexcept(Cannothrowassign<Trait>);
```

### 原型 4

```cpp
template<Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr const tuple<Types...>& asc::std::tuple::operator=(tuple<Types...>&& other) const noexcept(Cannothrowassign<Trait>);
```

### 原型 5

```cpp
template<class ...UTypes, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr const tuple<Types...>& asc::std::tuple::operator=(const tuple<UTypes...>& other) const noexcept(Cannothrowassign<Trait>);
```

### 原型 6

```cpp
template<class ...UTypes, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr const tuple<Types...>& asc::std::tuple::operator=(tuple<UTypes...>&& other) const noexcept(Cannothrowassign<Trait>);
```

### 原型 7

```cpp
template<class ...UTypes, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr tuple<Types...>& asc::std::tuple::operator=(const tuple<UTypes...>& other) noexcept(Cannothrowassign<Trait>);
```

### 原型 8

```cpp
template<class ...UTypes, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr tuple<Types...>& asc::std::tuple::operator=(tuple<UTypes...>&& other) noexcept(Cannothrowassign<Trait>);
```

### 原型 9

```cpp
template<class UTuple, enable_if_t<!Isascstdtuple<remove_cvref_t<UTuple>>, int>, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr const tuple<Types...>& asc::std::tuple::operator=(UTuple&& other) const noexcept(Cannothrowassign<Trait>);
```

### 原型 10

```cpp
template<class UTuple, enable_if_t<!Isascstdtuple<remove_cvref_t<UTuple>>, int>, Selectassignment Trait, enable_if_t<Canassign<Trait>, int>> constexpr tuple<Types...>& asc::std::tuple::operator=(UTuple&& other) noexcept(Cannothrowassign<Trait>);
```

### 原型 11

```cpp
template<class UTuple, enable_if_t<!Isascstdtuple<remove_cvref_t<UTuple>>, int>, enable_if_t<Tuplelikewithsize<UTuple, 0>, int>> constexpr const tuple<>& asc::std::tuple::operator=(UTuple&& other) const noexcept;
```

### 原型 12

```cpp
template<class UTuple, enable_if_t<!Isascstdtuple<remove_cvref_t<UTuple>>, int>, enable_if_t<Tuplelikewithsize<UTuple, 0>, int>> constexpr tuple<>& asc::std::tuple::operator=(UTuple&& other) noexcept;
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

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 11 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 12 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 3 | `const tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 4 | `const tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 5 | `const tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 6 | `const tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 7 | `tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 8 | `tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 9 | `const tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 10 | `tuple<Types...> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 11 | `const tuple<> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 12 | `tuple<> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配

## 调用示例

以下 Host 片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/tuple>

void example()
{
    asc::std::tuple<int, int> target(1, 2), source(3, 4);
    target = source;
}
```
