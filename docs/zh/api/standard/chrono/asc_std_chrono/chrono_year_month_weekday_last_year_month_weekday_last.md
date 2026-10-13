# asc::std::chrono::year_month_weekday_last::year_month_weekday_last

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

`asc::std::chrono::year_month_weekday_last::year_month_weekday_last` 按本页所列构造形态初始化 `year_month_weekday_last` 对象。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
constexpr year_month_weekday_last(const chrono::year& year_value, const chrono::month& month_value, const chrono::weekday_last& weekday_last_value) noexcept;
```

### 原型 2

```cpp
constexpr year_month_weekday_last(const year_month_weekday_last& year_value);
```

### 原型 3

```cpp
constexpr year_month_weekday_last(year_month_weekday_last&& year_value);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `year_value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `month_value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `weekday_last_value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `year_value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `year_value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |

## 约束说明

- 纯日历/组合/别名/字面量为Host、AI Core SIMD 编程 和 AI Core SIMT 编程
- system_clock仅为sys_time精确形状提供类型、rep/period/duration/time_point和is_steady类型

## 调用示例

以下 Host 片段以具体日期或时间类型演示调用；数值须满足本页约束。

```cpp
#include <asc/std/chrono>

void example()
{
    asc::std::chrono::year_month_weekday_last value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::weekday_last{asc::std::chrono::weekday{1}}};
    (void)value;
}
```
