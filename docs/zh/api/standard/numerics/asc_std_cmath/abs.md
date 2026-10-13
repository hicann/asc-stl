# asc::std::abs

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

头文件路径为：`<asc/std/cmath>`、`<asc/std/complex>`、`<asc/std/cstdlib>`。

`asc::std::abs`返回参数的绝对值；Device侧适用范围以本页float与执行位置约束为准。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr int abs(int x) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

此原型对应头文件：`<asc/std/cstdlib>`。

### 原型2

```cpp
namespace asc::std {
[[nodiscard]] constexpr long abs(long x) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

此原型对应头文件：`<asc/std/cstdlib>`。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr long long abs(long long x) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

此原型对应头文件：`<asc/std/cstdlib>`。

### 原型4

```cpp
namespace asc::std {
float abs(float x) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMT编程。

此原型对应头文件：`<asc/std/cmath>`。

### 原型5

```cpp
namespace asc::std {
template<class T> T abs(const complex<T>& value) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMT编程。

此原型对应头文件：`<asc/std/complex>`。

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求绝对值的整数输入（int）。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求绝对值的整数输入（long）。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求绝对值的整数输入（long long）。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求浮点绝对值的输入值（无量纲）。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数操作数的成分（实部与虚部）值类型，须为浮点类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求模（绝对值）的复数操作数，模为实部与虚部构成向量的长度。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `int` | 返回参数的绝对值。 |
| 原型2 | `long` | 返回参数的绝对值。 |
| 原型3 | `long long` | 返回参数的绝对值。 |
| 原型4 | `float` | 返回参数的绝对值。 |
| 原型5 | `T` | 返回参数的绝对值。 |

## 约束说明

- 提供整数重载及相应结果类型。
- 整数重载（原型1、原型2、原型3）要求参数的绝对值可由返回类型表示，例如`abs(INT_MIN)`不满足该要求，行为无定义。
- 提供float重载、标准 *f别名以及float lerp回移接口。
- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

decltype(auto) example(float x)
{
    return asc::std::abs(x);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
