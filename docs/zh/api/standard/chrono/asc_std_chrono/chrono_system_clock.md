# asc::std::chrono::system_clock

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

`asc::std::chrono::system_clock`提供系统时间点的类型标签、纳秒精度及`is_steady=false`；当前类型不提供now、`to_time_t`或`from_time_t`。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
class system_clock;
} // namespace asc::std::chrono
```

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。
- 本类型提供时间点、计时单位和相关类型别名；可调用的时钟操作以对应成员说明为准。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    static_assert(!asc::std::chrono::system_clock::is_steady);
    asc::std::chrono::system_clock::time_point epoch{};
    return epoch.time_since_epoch().count() == 0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
