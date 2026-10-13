# asc::std::optional::optional

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

头文件路径为：`<asc/std/optional>`。

`asc::std::optional::optional` 按本页所列构造形态初始化 `optional` 对象。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型 1

```cpp
constexpr asc::std::optional::optional() noexcept;
```

### 原型 2

```cpp
constexpr asc::std::optional::optional(asc::std::nullopt_t) noexcept;
```

### 原型 3

```cpp
constexpr asc::std::optional::optional(asc::std::optional&& other) noexcept(is_nothrow_move_constructible_v<T>);
```

### 原型 4

```cpp
constexpr asc::std::optional::optional(const asc::std::optional& other);
```

### 原型 5

```cpp
template<class U = T> constexpr explicit asc::std::optional::optional(U&& value);
```

### 原型 6

```cpp
template<class U> constexpr explicit asc::std::optional::optional(asc::std::optional<U>&& other);
```

### 原型 7

```cpp
template<class U> constexpr explicit asc::std::optional::optional(const asc::std::optional<U>& other);
```

### 原型 8

```cpp
template<class... Args> constexpr explicit asc::std::optional::optional(asc::std::in_place_t, Args&&... args);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | nullopt_t 空状态标记（nullopt 常量）；构造不含值的空 optional。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 移动来源 optional；其值被移动到新对象，移动后处于有效但未指定状态。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源 optional；其值被复制到新对象。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 构造所含值的来源类型（默认为 T）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 构造所含值的来源；左值被复制、右值被移动，右值移动后处于有效但未指定状态。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 来源 optional 所含值的类型，可与 T 不同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 移动来源 optional，所含值类型可与 T 不同；其值经转换移动，移动后处于有效但未指定状态。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 来源 optional 所含值的类型，可与 T 不同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制来源 optional，所含值类型可与 T 不同；其值经转换复制到新对象。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 原位构造所含值的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | in_place_t 原位构造标记；表示以 args 原位构造所含值。 |
| `args` | 输入/输出 | 原位构造所含值的实参；按序转发，右值被移动后处于有效但未指定状态。 |

## 约束说明

- T 必须是普通的非引用对象类型
- Host 遵循有效的 C++17 操作
- Device 侧构造、赋值、调用和交换所依赖的操作必须不抛出异常

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/optional>

void example()
{
    asc::std::optional<int> value{};
    (void)value.has_value();
}
```
