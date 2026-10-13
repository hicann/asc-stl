# asc::std::expected::transform

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

`asc::std::expected::transform`在保存有效值时变换该值，并把结果包装为同类状态对象。

标准语义参考：[cppreference `expected`](https://en.cppreference.com/w/cpp/header/expected)。

## 函数原型

所属类型：[`asc::std::expected`](expected.md)。

### 原型1

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Tp2, class Err2> constexpr auto transform(Fun&& function)&;
```

### 原型2

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Tp2, class Err2> constexpr auto transform(Fun&& function)&&;
```

### 原型3

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Tp2, class Err2> constexpr auto transform(Fun&& function) const&;
```

### 原型4

```cpp
// asc::std::expected 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Fun, class Tp2, class Err2> constexpr auto transform(Fun&& function) const&&;
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 对输入值执行本页操作的可调用对象类型。 |
| `Tp2` | 来源expected的成功值类型；该重载要求相应的成功值构造或传播可行。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“在保存有效值时变换该值，并把结果包装为同类状态对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 对输入值执行本页操作的可调用对象类型。 |
| `Tp2` | 来源expected的成功值类型；该重载要求相应的成功值构造或传播可行。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“在保存有效值时变换该值，并把结果包装为同类状态对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 对输入值执行本页操作的可调用对象类型。 |
| `Tp2` | 来源expected的成功值类型；该重载要求相应的成功值构造或传播可行。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“在保存有效值时变换该值，并把结果包装为同类状态对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Fun` | 对输入值执行本页操作的可调用对象类型。 |
| `Tp2` | 来源expected的成功值类型；该重载要求相应的成功值构造或传播可行。 |
| `Err2` | 来源expected的错误类型；该重载要求相应的错误值构造或传播可行。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `function` | 输入/输出 | 提供“在保存有效值时变换该值，并把结果包装为同类状态对象”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回按当前值或错误状态变换后形成的新状态对象。 |
| 原型2 | `auto` | 返回按当前值或错误状态变换后形成的新状态对象。 |
| 原型3 | `auto` | 返回按当前值或错误状态变换后形成的新状态对象。 |
| 原型4 | `auto` | 返回按当前值或错误状态变换后形成的新状态对象。 |

## 约束说明

- 支持所有cv/ref限定形式。
- Device侧可调用对象及结果构造必须不抛出异常。

## 调用示例

以下Host片段使用具体类型演示调用；访问值前须确认对象处于有值状态。

```cpp
#include <asc/std/expected>

decltype(auto) example()
{
    asc::std::expected<int, int> value(7);
    auto next = value.transform([](int input) { return input + 1; });
    return next;
}
```

## 关联API

- [`asc::std::expected`](expected.md)
- [本头文件的接口列表](asc_std_expected.md)
