# asc::std::chrono::hh_mm_ss

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

`asc::std::chrono::hh_mm_ss`将一个时长分解为符号、绝对值的小时、分钟、秒和小数秒，便于逐字段观察，再按`precision`组合回时长。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
template<class Duration> class hh_mm_ss;
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Duration` | 待拆分的时长类型；计数须满足chrono::abs的有符号条件并支持相应转换。 |

## 约束说明

- Duration须为duration，其计数须满足chrono::abs的有符号条件；当前实现不接受无符号计数。
- 原始时长的绝对值及拆分后的字段必须可表示；有符号最小负值不能取绝对值时不得传入。
- 负号单独保存，时、分、秒与小数秒字段保存绝对值的各部分。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds> time(asc::std::chrono::seconds(3661));
    return time.hours().count() == 1 && time.minutes().count() == 1 && time.seconds().count() == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
