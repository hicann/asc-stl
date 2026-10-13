# asc::std::chrono::month_weekday::month

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

`asc::std::chrono::month_weekday::month`返回当前日历组合中的月字段。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::month_weekday`](chrono_month_weekday.md)。

```cpp
// asc::std::chrono::month_weekday 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr chrono::month month() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `chrono::month` | 返回当前日历组合中的月字段。 |

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::month_weekday value{asc::std::chrono::month{2}, asc::std::chrono::weekday_indexed{asc::std::chrono::weekday{4}, 4}};
    return static_cast<unsigned int>(value.month()) == 2;
}
```

## 关联API

- [`asc::std::chrono::month_weekday`](chrono_month_weekday.md)
- [本头文件的接口列表](asc_std_chrono.md)
