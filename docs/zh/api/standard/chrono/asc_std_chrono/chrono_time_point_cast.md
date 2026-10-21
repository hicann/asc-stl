# asc::std::chrono::time_point_cast

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

`asc::std::chrono::time_point_cast`把时间点转换为指定精度的时间点类型。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Clock, class Duration> [[nodiscard]] constexpr time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>& value);
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 转换到的目标时长类型，作为结果时间点的计时精度。 |
| `Clock` | 时间点所属的时钟类型，如system_clock。 |
| `Duration` | 源时间点的时长类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的时间点；目标计数为整数时，不能表示的分数部分向零截断；浮点目标保留其可表示的分数并按浮点转换舍入。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `time_point<Clock, ToDuration>` | 返回按所选精度和舍入规则转换后的时长或时间点。 |

## 约束说明

- 支持用户定义时钟、值运算以及六个显式关系运算符。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/chrono>

decltype(auto) example()
{
    asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::milliseconds> value{asc::std::chrono::milliseconds{1500}};
    return asc::std::chrono::time_point_cast<asc::std::chrono::seconds>(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
