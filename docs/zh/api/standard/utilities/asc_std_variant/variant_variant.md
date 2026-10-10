# asc::std::variant::variant

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

头文件路径为：`<asc/std/variant>`。

`asc::std::variant::variant` 按本页所列构造形态初始化 `variant` 对象。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

### 原型 1

```cpp
constexpr variant(const variant<Types...>& value);
```

### 原型 2

```cpp
constexpr variant(variant<Types...>&& value);
```

### 原型 3

```cpp
template<bool Dummy, class> constexpr variant() noexcept(is_nothrow_default_constructible_v<Firsttype>);
```

### 原型 4

```cpp
template<class Arg, class, class Constraints, class> constexpr variant(Arg&& value) noexcept(Constraints::Nothrowconstructible);
```

### 原型 5

```cpp
template<class T, class ...Args, size_t Index, class Constraints, class> constexpr variant(in_place_type_t<T> tag, Args&&... args) noexcept(Constraints::Nothrowconstructible);
```

### 原型 6

```cpp
template<size_t Index, class ...Args, class Constraints, class> constexpr variant(in_place_index_t<Index> tag, Args&&... args) noexcept(Constraints::Nothrowconstructible);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Dummy` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `未命名参数2` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Arg` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数2` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |
| `Constraints` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数4` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Constraints` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数5` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `variant` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |
| `Constraints` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `未命名参数4` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `variant` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/variant>

void example()
{
    asc::std::variant<int, float> source(7);
    asc::std::variant<int, float> copy(source);
    (void)copy.index();
}
```
