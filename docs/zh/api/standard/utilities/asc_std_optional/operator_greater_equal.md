# asc::std::operator>=（函数模板）

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

头文件路径为：`<asc/std/optional>`、`<asc/std/string_view>`、`<asc/std/variant>`。

`asc::std::operator>=` 判断左操作数是否不小于右操作数。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型 1

```cpp
template<class ...Types> [[nodiscard]] constexpr bool asc::std::operator>=(const variant<Types...>& left, const variant<Types...>& right);
```

此原型对应头文件：`<asc/std/variant>`。

### 原型 2

```cpp
template<class T, class U> constexpr bool asc::std::operator>=(const T& value, const asc::std::optional<U>& optional_value);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 3

```cpp
template<class T, class U> constexpr bool asc::std::operator>=(const asc::std::optional<T>& left, const asc::std::optional<U>& right);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 4

```cpp
template<class T, class U> constexpr bool asc::std::operator>=(const asc::std::optional<T>& optional_value, const U& value);
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 5

```cpp
template<class T> constexpr bool asc::std::operator>=(asc::std::nullopt_t, const asc::std::optional<T>& value) noexcept;
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 6

```cpp
template<class T> constexpr bool asc::std::operator>=(const asc::std::optional<T>& value, asc::std::nullopt_t) noexcept;
```

此原型对应头文件：`<asc/std/optional>`。

### 原型 7

```cpp
template<int T> [[nodiscard]] constexpr bool asc::std::operator>=(basic_string_view<CharT, Traits> left, type_identity_t<basic_string_view<CharT, Traits>> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

### 原型 8

```cpp
template<unsigned int> [[nodiscard]] constexpr bool asc::std::operator>=(type_identity_t<basic_string_view<CharT, Traits>> left, basic_string_view<CharT, Traits> right) noexcept;
```

此原型对应头文件：`<asc/std/string_view>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Types` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `optional_value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `optional_value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | 提供“判断左操作数是否不小于右操作数”所需的输入对象；类型须满足所选原型约束。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `asc` | 输入 | 提供“判断左操作数是否不小于右操作数”所需的输入对象；类型须满足所选原型约束。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `未命名参数1` | 未命名的编译期参数；调用方通常由上下文推导或使用默认值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与本次比较或运算的左侧操作数。 |
| `right` | 输入 | 参与本次比较或运算的右侧操作数。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 4 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 5 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 6 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 7 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 8 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- Device 侧备选类型以及所选构造、赋值和交换操作必须不抛出异常
- index、operator*、emplace、swap 和 visit 仅提供非抛出路径
- T 必须是普通的非引用对象类型
- Host 遵循有效的 C++17 操作
- Device 侧构造、赋值、调用和交换所依赖的操作必须不抛出异常
- 提供构造、迭代和除 at 外的访问接口，以及 remove_prefix、remove_suffix、swap、data、size、starts_with、ends_with 和非抛出的比较/查找接口
- AI Core SIMD 编程 仅支持 local 或 generic 地址空间的普通字符指针

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/optional>

template <class T, class U>
decltype(auto) example(const T& value, const asc::std::optional<U>& optional_value)
{
    return asc::std::operator>=(value, optional_value);
}
```
