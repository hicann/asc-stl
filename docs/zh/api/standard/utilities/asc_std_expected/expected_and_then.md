# asc::std::expected::and_then

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

头文件路径为：`<asc/std/expected>`。

`asc::std::expected::and_then` 在保存有效值时调用函数，并传播其返回的状态对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

### 原型 1

```cpp
template<class Function> constexpr auto asc::std::expected::and_then(Function function) const;
```

### 原型 2

```cpp
template<class Fun, class Err2> constexpr auto asc::std::expected::and_then(Fun&& function)&;
```

### 原型 3

```cpp
template<class Fun, class Err2> constexpr auto asc::std::expected::and_then(Fun&& function)&&;
```

### 原型 4

```cpp
template<class Fun, class Err2> constexpr auto asc::std::expected::and_then(Fun&& function) const&;
```

### 原型 5

```cpp
template<class Fun, class Err2> constexpr auto asc::std::expected::and_then(Fun&& function) const&&;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Function` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为 expected 类对象。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入 | 以保存的期望值为实参调用的可调用对象，调用形式 function(期望值)；仅含期望值时调用，其返回的 expected 作为结果传播。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为 expected 类对象。 |
| `Err2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式 function(期望值)；仅含期望值时调用，其返回的 expected 作为结果传播。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为 expected 类对象。 |
| `Err2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式 function(期望值)；仅含期望值时调用，其返回的 expected 作为结果传播。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为 expected 类对象。 |
| `Err2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式 function(期望值)；仅含期望值时调用，其返回的 expected 作为结果传播。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为 expected 类对象。 |
| `Err2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式 function(期望值)；仅含期望值时调用，其返回的 expected 作为结果传播。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `auto` | 返回的状态对象。 |
| 原型 2 | `auto` | 返回的状态对象。 |
| 原型 3 | `auto` | 返回的状态对象。 |
| 原型 4 | `auto` | 返回的状态对象。 |
| 原型 5 | `auto` | 返回的状态对象。 |

## 约束说明

- T 必须为非 void 类型，E 必须为对象类型
- 适用操作必须不抛出异常
- 提供构造、赋值、emplace 和 swap
- 支持所有 cv/ref 限定形式
- Device 侧可调用对象及结果构造必须不抛出异常

## 调用示例

以下 Host 片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    auto next = value.and_then([](int input) { return asc::std::expected<int, int>(input + 1); });
    return next;
}
```
