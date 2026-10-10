# asc::std::optional::operator=

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

`asc::std::optional::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 函数原型

### 原型 1

```cpp
constexpr asc::std::optional& asc::std::optional::operator=(asc::std::nullopt_t) noexcept;
```

### 原型 2

```cpp
constexpr asc::std::optional& asc::std::optional::operator=(asc::std::optional&& other) noexcept(is_nothrow_move_constructible_v<T>&& is_nothrow_move_assignable_v<T>);
```

### 原型 3

```cpp
constexpr asc::std::optional& asc::std::optional::operator=(const asc::std::optional& other);
```

### 原型 4

```cpp
template<class U> constexpr asc::std::optional& asc::std::optional::operator=(U&& value);
```

### 原型 5

```cpp
template<class U> constexpr asc::std::optional& asc::std::optional::operator=(asc::std::optional<U>&& other);
```

### 原型 6

```cpp
template<class U> constexpr asc::std::optional& asc::std::optional::operator=(const asc::std::optional<U>& other);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `asc` | 输入 | 提供“按所选赋值重载更新对象，并返回规定的结果”所需的输入对象；类型须满足所选原型约束。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 3 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 4 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 5 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 6 | `asc::std::optional&` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

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
    asc::std::optional<int> value(7);
    value = asc::std::nullopt;
}
```
