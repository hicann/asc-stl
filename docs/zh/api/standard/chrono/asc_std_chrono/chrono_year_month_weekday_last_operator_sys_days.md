# asc::std::chrono::year_month_weekday_last::operator sys_days

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

`asc::std::chrono::year_month_weekday_last::operator sys_days`由`<asc/std/chrono>`提供，把年月末星期换算为系统纪元天数精度的时间点。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型为[`year_month_weekday_last`](chrono_year_month_weekday_last.md)。

```cpp
[[nodiscard]] constexpr operator sys_days() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::chrono::sys_days` | 该日期在系统时间线上的日精度时间点。 |

## 约束说明

- 换算定位到该月最后一个同星期日期，结果面向系统纪元。
- 调用月末日查询或依赖该查询的转换前，月字段必须在1到12之间；完整有效性可由来源对象的ok()检查。无效月份不得用于月长表查询。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_weekday_last value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::weekday_last{asc::std::chrono::weekday{4}}};
    return static_cast<asc::std::chrono::sys_days>(value).time_since_epoch().count() == 19782;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
