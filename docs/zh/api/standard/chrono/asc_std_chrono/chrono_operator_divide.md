# asc::std::chrono::`operator/`

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

`asc::std::chrono::operator/`由`<asc/std/chrono>`提供，执行时长维度的时长除以标量运算。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
namespace asc::std::chrono {
template <class Rep2, enable_if_t<!__is_asc_std_duration_v<Rep2> && is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period> operator/(const duration& lhs, const Rep2& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std::chrono {
template <class Rep2, class Period2> constexpr common_type_t<Rep, Rep2> operator/(const duration& lhs, const duration<Rep2, Period2>& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std::chrono {
constexpr month_day operator/(const chrono::day& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型4

```cpp
namespace asc::std::chrono {
constexpr year_month operator/(const chrono::year& lhs, const chrono::month& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型5

```cpp
namespace asc::std::chrono {
constexpr year_month operator/(const chrono::year& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型6

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(const year_month& lhs, const day& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型7

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(const year_month& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型8

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(const year& lhs, const month_day& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型9

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(int lhs, const month_day& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型10

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(const month_day& lhs, const year& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型11

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator/(const month_day& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型12

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator/(const year_month& lhs, last_spec rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型13

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator/(const year& lhs, const month_day_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型14

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator/(int lhs, const month_day_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型15

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator/(const month_day_last& lhs, const year& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型16

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator/(const month_day_last& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型17

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator/(const year_month& lhs, const weekday_indexed& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型18

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator/(const year& lhs, const chrono::month_weekday_indexed& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型19

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator/(int lhs, const chrono::month_weekday_indexed& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型20

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator/(const chrono::month_weekday_indexed& lhs, const year& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型21

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator/(const chrono::month_weekday_indexed& lhs, int rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型22

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator/(const year_month& lhs, const weekday_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型23

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator/(const year& lhs, const chrono::month_weekday_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型24

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator/(int lhs, const chrono::month_weekday_last& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型25

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator/(const chrono::month_weekday_last& lhs, const year& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型26

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator/(const chrono::month_weekday_last& lhs, int rhs) noexcept;
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
| `duration<common_type_t<Rep, Rep2>, Period>` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `common_type_t<Rep, Rep2>` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `month_day` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `year_month` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `year_month_day` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `year_month_day_last` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `year_month_weekday` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |
| `year_month_weekday_last` | duration除标量时返回缩放后的duration，两个duration相除时返回标量商；日历的 / 形式组合相应的年、月、日或星期字段。 |

## 约束说明

- 右操作数须为可转换到公共计数类型的标量且不得为时长类型。
- 两个时长先转换为公共时长类型，商为公共计数类型的计数值。
- 右操作数为月份取值，语义等价于先以该整数构造月份再组装month_day。
- 两个操作数分别提供年份与月份。
- 右操作数先按月份取值构造月份。
- 左操作数提供年份与月份，右操作数提供日期。
- 右操作数先按日期取值构造日期。
- 左操作数提供年份，右操作数提供月份与日期。
- 左操作数先按年份取值构造年份。
- 交换方向的组装语义，结果与年份在前时一致。
- 右操作数先按年份取值构造年份。
- 右操作数为月末标记，组装结果表示该年该月的最后一天。
- 左操作数提供年份，右操作数提供月份与月末标记。
- 左操作数提供年份与月份，右操作数提供星期与序号。
- 左操作数提供年份，右操作数提供月份与带序号星期。
- 左操作数提供年份与月份，右操作数提供星期与月末标记。
- 左操作数提供年份，右操作数提供月份与月末星期。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::seconds left{2}, right{3};
    return right / left == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
