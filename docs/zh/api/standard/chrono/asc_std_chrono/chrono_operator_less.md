# asc::std::chrono::`operator<`

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::operator<`由`<asc/std/chrono>`提供，比较两个时长的小于关系。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
namespace asc::std::chrono {
template <class Rep2, class Period2> constexpr bool operator<(const duration<Rep, Period>& lhs, const duration<Rep2, Period2>& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const month& lhs, const month& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const month_day_last& lhs, const month_day_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型4

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const weekday& lhs, const weekday& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型5

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const year_month& lhs, const year_month& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型6

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const year_month_day& lhs, const year_month_day& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型7

```cpp
namespace asc::std::chrono {
constexpr bool operator<(const year_month_day_last& lhs, const year_month_day_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 另一时长或标量的计数类型；运算时与Rep形成公共类型。 |
| `Period2` | 另一时长的计时周期，是表示秒比例的ratio类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `rhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 对应的相等／顺序比较表达式成立时为true，否则为false。 |

## 约束说明

- 两个时长先转换为公共时长类型再比较计数值。
- 按内部存储的无符号月份值逐位比较。
- 按month()的取值比较大小先后。
- 按c_encoding()返回的星期编码值比较大小。
- 按year()优先、month()其次的字典序比较。
- 按year()、month()、day()的字典序比较。
- 按year()、month()的字典序比较。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::seconds left{2}, right{3};
    return left < right;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
