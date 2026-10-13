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

`asc::std::expected::and_then`在保存有效值时调用函数，并传播其返回的状态对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

所属类型：[`asc::std::expected`](expected.md)。

### 原型1

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Function> constexpr auto and_then(Function function) const;
```

### 原型2

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Err2> constexpr auto and_then(Fun&& function)&;
```

### 原型3

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Err2> constexpr auto and_then(Fun&& function)&&;
```

### 原型4

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Err2> constexpr auto and_then(Fun&& function) const&;
```

### 原型5

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Err2> constexpr auto and_then(Fun&& function) const&&;
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Function` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为expected类对象。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入 | 以保存的期望值为实参调用的可调用对象，调用形式function(期望值)；仅含期望值时调用，其返回的expected作为结果传播。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为expected类对象。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式function(期望值)；仅含期望值时调用，其返回的expected作为结果传播。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为expected类对象。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式function(期望值)；仅含期望值时调用，其返回的expected作为结果传播。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为expected类对象。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式function(期望值)；仅含期望值时调用，其返回的expected作为结果传播。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 以保存的期望值为实参调用的可调用对象类型；调用结果须为expected类对象。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 以保存的期望值为实参调用的可调用对象，调用形式function(期望值)；仅含期望值时调用，其返回的expected作为结果传播。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回的状态对象。 |
| 原型2 | `auto` | 返回的状态对象。 |
| 原型3 | `auto` | 返回的状态对象。 |
| 原型4 | `auto` | 返回的状态对象。 |
| 原型5 | `auto` | 返回的状态对象。 |

## 约束说明

- T必须为非void类型，E必须为对象类型。
- 适用操作必须不抛出异常。
- 提供构造、赋值、emplace和swap。
- 支持所有cv/ref限定形式。
- Device侧可调用对象及结果构造必须不抛出异常。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    auto next = value.and_then([](int input) { return asc::std::expected<int, int>(input + 1); });
    return next;
}
```

## 关联API

- [`asc::std::expected`](expected.md)
- [本头文件的接口列表](asc_std_expected.md)
