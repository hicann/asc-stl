# asc::std::chrono::year_month_weekday_last::ok

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

`asc::std::chrono::year_month_weekday_last::ok`判断当前日历字段组合是否表示有效日期。

`year_month_weekday_last`表示"某年某月的最后一个星期几"：年取值在`[-32767, 32767]`、月取值在`[1, 12]`且星期取值在`[0, 6]`（0表示星期日、6表示星期六）时返回`true`，否则返回`false`。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md)。

```cpp
// asc::std::chrono::year_month_weekday_last 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr bool ok() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_weekday_last value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::weekday_last{asc::std::chrono::weekday{4}}};
    return value.ok();
}
```

## 关联API

- [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md)
- [本头文件的接口列表](asc_std_chrono.md)
