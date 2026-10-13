# asc::std::chrono::time_point

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

`asc::std::chrono::time_point`表示日期、时间点或时长计算中的`time_point`值类型。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
template<class Clock, class Duration> class time_point;
} // namespace asc::std::chrono
```

## 约束说明

- 支持用户定义时钟、值运算以及六个显式关系运算符。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    using point = asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds>;
    point start(asc::std::chrono::seconds(3));
    const point end = start + asc::std::chrono::seconds(2);
    return start.time_since_epoch().count() == 3 && (end - start).count() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
