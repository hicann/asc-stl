# asc::std::chrono::operator/

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

`asc::std::chrono::operator/` 由 `<asc/std/chrono>` 提供，执行时长维度的时长除以标量运算。接口遵循对应 C++ 标准设施的语义；ASC-STL 的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
template <class Rep2, enable_if_t<!__is_asc_std_duration_v<Rep2> && is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period> asc::std::chrono::operator/(const duration& lhs, const Rep2& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 2

```cpp
template <class Rep2, class Period2> constexpr common_type_t<Rep, Rep2> asc::std::chrono::operator/(const duration& lhs, const duration<Rep2, Period2>& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 3

```cpp
constexpr month_day asc::std::chrono::operator/(const chrono::day& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 4

```cpp
constexpr year_month asc::std::chrono::operator/(const chrono::year& lhs, const chrono::month& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 5

```cpp
constexpr year_month asc::std::chrono::operator/(const chrono::year& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 6

```cpp
constexpr year_month_day asc::std::chrono::operator/(const year_month& lhs, const day& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 7

```cpp
constexpr year_month_day asc::std::chrono::operator/(const year_month& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 8

```cpp
constexpr year_month_day asc::std::chrono::operator/(const year& lhs, const month_day& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 9

```cpp
constexpr year_month_day asc::std::chrono::operator/(int lhs, const month_day& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 10

```cpp
constexpr year_month_day asc::std::chrono::operator/(const month_day& lhs, const year& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 11

```cpp
constexpr year_month_day asc::std::chrono::operator/(const month_day& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 12

```cpp
constexpr year_month_day_last asc::std::chrono::operator/(const year_month& lhs, last_spec rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 13

```cpp
constexpr year_month_day_last asc::std::chrono::operator/(const year& lhs, const month_day_last& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 14

```cpp
constexpr year_month_day_last asc::std::chrono::operator/(int lhs, const month_day_last& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 15

```cpp
constexpr year_month_day_last asc::std::chrono::operator/(const month_day_last& lhs, const year& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 16

```cpp
constexpr year_month_day_last asc::std::chrono::operator/(const month_day_last& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 17

```cpp
constexpr year_month_weekday asc::std::chrono::operator/(const year_month& lhs, const weekday_indexed& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 18

```cpp
constexpr year_month_weekday asc::std::chrono::operator/(const year& lhs, const chrono::month_weekday_indexed& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 19

```cpp
constexpr year_month_weekday asc::std::chrono::operator/(int lhs, const chrono::month_weekday_indexed& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 20

```cpp
constexpr year_month_weekday asc::std::chrono::operator/(const chrono::month_weekday_indexed& lhs, const year& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 21

```cpp
constexpr year_month_weekday asc::std::chrono::operator/(const chrono::month_weekday_indexed& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 22

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator/(const year_month& lhs, const weekday_last& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 23

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator/(const year& lhs, const chrono::month_weekday_last& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 24

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator/(int lhs, const chrono::month_weekday_last& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 25

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator/(const chrono::month_weekday_last& lhs, const year& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 26

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator/(const chrono::month_weekday_last& lhs, int rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep2` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |
| `Period2` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `rhs` | 输入 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `&& is_convertible_v<const Rep2&, common_type_t<Rep, Rep2>>, int> = 0> constexpr duration<common_type_t<Rep, Rep2>, Period>` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `common_type_t<Rep, Rep2>` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `month_day` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_day` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_day_last` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_weekday` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_weekday_last` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 右操作数须为可转换到公共计数类型的标量且不得为时长类型
- 两个时长先转换为公共时长类型，商为公共计数类型的计数值
- 右操作数为月份取值，语义等价于先以该整数构造月份再组装month_day
- 两个操作数分别提供年份与月份
- 右操作数先按月份取值构造月份
- 左操作数提供年份与月份，右操作数提供日期
- 右操作数先按日期取值构造日期
- 左操作数提供年份，右操作数提供月份与日期
- 左操作数先按年份取值构造年份
- 交换方向的组装语义，结果与年份在前时一致
- 右操作数先按年份取值构造年份
- 右操作数为月末标记，组装结果表示该年该月的最后一天
- 左操作数提供年份，右操作数提供月份与月末标记
- 左操作数提供年份与月份，右操作数提供星期与序号
- 左操作数提供年份，右操作数提供月份与带序号星期
- 左操作数提供年份与月份，右操作数提供星期与月末标记
- 左操作数提供年份，右操作数提供月份与月末星期

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

void example()
{
    const asc::std::chrono::year_month& lhs{};
    const asc::std::chrono::day& rhs{};
    (void)(lhs / rhs);
}
```
