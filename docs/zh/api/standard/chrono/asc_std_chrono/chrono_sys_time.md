# asc::std::chrono::sys_time

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

`asc::std::chrono::sys_time`是`Clock`为`system_clock`、计时精度为`Duration`的时间点别名；保存系统纪元以来的计数。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
template<class Duration> using sys_time = time_point<system_clock, Duration>;
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Duration` | 系统时间点的时长类型，决定计数精度。 |

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using actual_type = asc::std::chrono::sys_time<asc::std::chrono::seconds>;
using expected_type = asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds>;
static_assert(asc::std::is_same_v<actual_type, expected_type>);
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
