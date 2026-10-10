# asc::std::tuple::tuple

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

`asc::std::tuple::tuple` 按本页所列构造形态初始化 `tuple` 对象。

标准语义参考：[cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple)。

## 函数原型

### 原型 1

```cpp
tuple(const tuple<Types...>& values);
```

### 原型 2

```cpp
tuple(tuple<Types...>&& values);
```

### 原型 3

```cpp
constexpr tuple() noexcept;
```

### 原型 4

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple() noexcept((is_nothrow_default_constructible_v<T>&& ...));
```

### 原型 5

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(const T&... values) noexcept(Tupleallnothrowcopyconstructiblev<T...>);
```

### 原型 6

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple() noexcept((is_nothrow_default_constructible_v<T>&& ...));
```

### 原型 7

```cpp
template<Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(const T&... values) noexcept(Tupleallnothrowcopyconstructiblev<T...>);
```

### 原型 8

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(const tuple<UTypes...>&& values) noexcept(NothrowTupleLike<const tuple<UTypes...>&&>::value);
```

### 原型 9

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(const tuple<UTypes...>& values) noexcept(NothrowTupleLike<const tuple<UTypes...>&>::value);
```

### 原型 10

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(tuple<UTypes...>&& values) noexcept(NothrowTupleLike<tuple<UTypes...>&&>::value);
```

### 原型 11

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(tuple<UTypes...>& values) noexcept(NothrowTupleLike<tuple<UTypes...>&>::value);
```

### 原型 12

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(const tuple<UTypes...>&& values) noexcept(NothrowTupleLike<const tuple<UTypes...>&&>::value);
```

### 原型 13

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(const tuple<UTypes...>& values) noexcept(NothrowTupleLike<const tuple<UTypes...>&>::value);
```

### 原型 14

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(tuple<UTypes...>&& values) noexcept(NothrowTupleLike<tuple<UTypes...>&&>::value);
```

### 原型 15

```cpp
template<class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(tuple<UTypes...>& values) noexcept(NothrowTupleLike<tuple<UTypes...>&>::value);
```

### 原型 16

```cpp
template<class ...UTypes, enable_if_t<(sizeof...(UTypes) < sizeof...(T)), int>, enable_if_t<(sizeof...(UTypes) != 0), int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(UTypes&&... arg1);
```

### 原型 17

```cpp
template<class ...UTypes, enable_if_t<sizeof...(T) != 0, int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(UTypes&&... values) noexcept(NothrowVariadic<UTypes...>::value);
```

### 原型 18

```cpp
template<class ...UTypes, enable_if_t<sizeof...(T) != 0, int>, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(UTypes&&... values) noexcept(NothrowVariadic<UTypes...>::value);
```

### 原型 19

```cpp
template<class Allocator, Selectconstructor Trait, enable_if_t<Canconstruct<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, const tuple<Types...>& source) noexcept(Tupleallnothrowcopyconstructiblev<Types...>);
```

### 原型 20

```cpp
template<class Allocator, Selectconstructor Trait, enable_if_t<Canconstruct<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, tuple<Types...>&& source) noexcept(Tupleallnothrowmoveconstructiblev<Types...>);
```

### 原型 21

```cpp
template<class Allocator, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator) noexcept((is_nothrow_default_constructible_v<T>&& ...));
```

### 原型 22

```cpp
template<class Allocator, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator) noexcept((is_nothrow_default_constructible_v<T>&& ...));
```

### 原型 23

```cpp
template<class Allocator, class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> tuple(allocator_arg_t tag, const Allocator& allocator, UTypes&&... source) noexcept(NothrowVariadic<UTypes...>::value);
```

### 原型 24

```cpp
template<class Allocator, class ...UTypes, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> tuple(allocator_arg_t tag, const Allocator& allocator, UTypes&&... source) noexcept(NothrowVariadic<UTypes...>::value);
```

### 原型 25

```cpp
template<class Allocator, class Tuple, enable_if_t<Disambiguatetuplelike<Tuple>::value, int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, Tuple&& source) noexcept(NothrowTupleLike<Tuple>::value);
```

### 原型 26

```cpp
template<class Allocator, class Tuple, enable_if_t<Disambiguatetuplelike<Tuple>::value, int>, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, Tuple&& source) noexcept(NothrowTupleLike<Tuple>::value);
```

### 原型 27

```cpp
template<class Allocator, class U> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, array<U, 0> source) noexcept;
```

### 原型 28

```cpp
template<class Allocator, enable_if_t<sizeof...(T) != 0, int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, const T&... source) noexcept(Tupleallnothrowcopyconstructiblev<T...>);
```

### 原型 29

```cpp
template<class Allocator, enable_if_t<sizeof...(T) != 0, int>, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, const T&... source) noexcept(Tupleallnothrowcopyconstructiblev<T...>);
```

### 原型 30

```cpp
template<class Allocator> constexpr tuple(allocator_arg_t tag, const Allocator& allocator) noexcept;
```

### 原型 31

```cpp
template<class Allocator> constexpr tuple(allocator_arg_t tag, const Allocator& allocator, const tuple<>& source) noexcept;
```

### 原型 32

```cpp
template<class Tuple, enable_if_t<Disambiguatetuplelike<Tuple>::value, int>, Selectconstructor Trait, enable_if_t<Canconstructexplicitly<Trait>, int>> constexpr tuple(Tuple&& values) noexcept(NothrowTupleLike<Tuple>::value);
```

### 原型 33

```cpp
template<class Tuple, enable_if_t<Disambiguatetuplelike<Tuple>::value, int>, Selectconstructor Trait, enable_if_t<Canconstructimplicitly<Trait>, int>> constexpr tuple(Tuple&& values) noexcept(NothrowTupleLike<Tuple>::value);
```

### 原型 34

```cpp
template<class TupleOfIteratorReferences, enable_if_t<Istupleofiteratorreferencesv<TupleOfIteratorReferences>, int>, enable_if_t<(tuple_size<TupleOfIteratorReferences>::value == sizeof...(T)), int>> constexpr tuple(TupleOfIteratorReferences&& values);
```

### 原型 35

```cpp
template<class U> constexpr tuple(array<U, 0> values) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

无参数。

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

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
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 11 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 12 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 13 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 14 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 15 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 16 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |

### 原型 17 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 18 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 19 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 20 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 21 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 22 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 23 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 24 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `UTypes` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 25 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Tuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数5` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 26 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `Tuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数5` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 27 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 28 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 29 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 30 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

### 原型 31 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Allocator` | 为对象或元素分配和释放存储的分配器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 负责本次对象存储分配与释放的分配器。 |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |
| `source` | 输入 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 32 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 33 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tuple` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `Trait` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `匿名约束参数4` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 34 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `TupleOfIteratorReferences` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 35 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `values` | 输入 | 参与操作或用于初始化、比较的值。 |

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配

## 调用示例

以下 Host 片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/tuple>

void example()
{
    asc::std::tuple<int, int> value{};
    (void)value;
}
```
