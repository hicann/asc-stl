# asc::std::chrono::`operator-`

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

`asc::std::chrono::operator-`由`<asc/std/chrono>`提供，执行时长维度的求差运算。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
namespace asc::std::chrono {
template <class Rep2, class Period2> constexpr common_type_t<duration, duration<Rep2, Period2>> operator-(const duration& lhs, const duration<Rep2, Period2>& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std::chrono {
constexpr month operator-(const month& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std::chrono {
constexpr months operator-(const month& lhs, const month& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型4

```cpp
namespace asc::std::chrono {
template <class Rep2, class Period2> constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator-(const time_point& lhs, const chrono::duration<Rep2, Period2>& rhs);
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型5

```cpp
namespace asc::std::chrono {
constexpr months operator-(const year_month& lhs, const year_month& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型6

```cpp
namespace asc::std::chrono {
constexpr year_month operator-(const year_month& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型7

```cpp
namespace asc::std::chrono {
constexpr year_month operator-(const year_month& lhs, const years& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型8

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator-(const year_month_day& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型9

```cpp
namespace asc::std::chrono {
constexpr year_month_day operator-(const year_month_day& lhs, const years& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型10

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator-(const year_month_day_last& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型11

```cpp
namespace asc::std::chrono {
constexpr year_month_day_last operator-(const year_month_day_last& lhs, const years& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型12

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator-(const year_month_weekday& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型13

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday operator-(const year_month_weekday& lhs, const years& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型14

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator-(const year_month_weekday_last& lhs, const months& rhs) noexcept;
} // namespace asc::std::chrono
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型15

```cpp
namespace asc::std::chrono {
constexpr year_month_weekday_last operator-(const year_month_weekday_last& lhs, const years& rhs) noexcept;
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
| `common_type_t<duration, duration<Rep2, Period2>>` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `month` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `months` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `year_month` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `year_month_day` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `year_month_day_last` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `year_month_weekday` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |
| `year_month_weekday_last` | 减法结果：时长／时间点差使用公共duration；日历形式产生相应的月份差或偏移后的日期组成。 |

## 约束说明

- 两个时长先转换为公共时长类型后相减。
- 月数按十二进制回绕，结果保持在标准月份取值范围内。
- 两个月份的差值结果保证落在一个年度范围之内。
- 时长与时间点的精度先取公共类型，结果为该精度下的时间点。
- 差值为年份差折算的月数与月份差之和。
- 等价于加上相反数。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::seconds left{2}, right{3};
    return (right - left).count() == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
