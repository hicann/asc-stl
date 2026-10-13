# asc::std::chrono::time_point::min

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

`asc::std::chrono::time_point::min`返回该类型允许的最小值。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::time_point`](chrono_time_point.md)。

```cpp
// asc::std::chrono::time_point 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr time_point<Clock, Duration> min() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `time_point<Clock, Duration>` | 返回该类型允许的最小值。 |

## 约束说明

- 支持用户定义时钟、值运算以及六个显式关系运算符。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds> value{asc::std::chrono::seconds{7}};
    return value.min() < value;
}
```

## 关联API

- [`asc::std::chrono::time_point`](chrono_time_point.md)
- [本头文件的接口列表](asc_std_chrono.md)
