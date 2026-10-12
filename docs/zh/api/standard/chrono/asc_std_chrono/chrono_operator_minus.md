# asc::std::chrono::operator-

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

`asc::std::chrono::operator-` 由 `<asc/std/chrono>` 提供，执行时长维度的求差运算。接口遵循对应 C++ 标准设施的语义；ASC-STL 的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
template <class Rep2, class Period2> constexpr common_type_t<duration, duration<Rep2, Period2>> asc::std::chrono::operator-(const duration& lhs, const duration<Rep2, Period2>& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 2

```cpp
constexpr month asc::std::chrono::operator-(const month& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 3

```cpp
constexpr months asc::std::chrono::operator-(const month& lhs, const month& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 4

```cpp
template <class Rep2, class Period2> constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> asc::std::chrono::operator-(const time_point& lhs, const chrono::duration<Rep2, Period2>& rhs)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 5

```cpp
constexpr months asc::std::chrono::operator-(const year_month& lhs, const year_month& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 6

```cpp
constexpr year_month asc::std::chrono::operator-(const year_month& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 7

```cpp
constexpr year_month asc::std::chrono::operator-(const year_month& lhs, const years& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 8

```cpp
constexpr year_month_day asc::std::chrono::operator-(const year_month_day& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 9

```cpp
constexpr year_month_day asc::std::chrono::operator-(const year_month_day& lhs, const years& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 10

```cpp
constexpr year_month_day_last asc::std::chrono::operator-(const year_month_day_last& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 11

```cpp
constexpr year_month_day_last asc::std::chrono::operator-(const year_month_day_last& lhs, const years& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 12

```cpp
constexpr year_month_weekday asc::std::chrono::operator-(const year_month_weekday& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 13

```cpp
constexpr year_month_weekday asc::std::chrono::operator-(const year_month_weekday& lhs, const years& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 14

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator-(const year_month_weekday_last& lhs, const months& rhs) noexcept
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 15

```cpp
constexpr year_month_weekday_last asc::std::chrono::operator-(const year_month_weekday_last& lhs, const years& rhs) noexcept
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
| `common_type_t<duration, duration<Rep2, Period2>>` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `month` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `months` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_day` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_day_last` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_weekday` | 返回该操作产生的值，具体含义由所选原型确定。 |
| `year_month_weekday_last` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 两个时长先转换为公共时长类型后相减
- 月数按十二进制回绕，结果保持在标准月份取值范围内
- 两个月份的差值结果保证落在一个年度范围之内
- 时长与时间点的精度先取公共类型，结果为该精度下的时间点
- 差值为年份差折算的月数与月份差之和
- 等价于加上相反数

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

void example()
{
    const asc::std::chrono::month& lhs{};
    const asc::std::chrono::months& rhs{};
    (void)(lhs - rhs);
}
```
