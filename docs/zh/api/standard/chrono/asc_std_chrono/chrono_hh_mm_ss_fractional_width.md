# asc::std::chrono::hh_mm_ss::fractional_width

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

`asc::std::chrono::hh_mm_ss::fractional_width`给出时间表示中秒以下部分的十进制位数。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

fractional_width是hh_mm_ss的静态constexpr成员。下例为查询该公开成员的表达式，不新增成员。

```cpp
template<class Duration>
inline constexpr unsigned fractional_width_of =
    asc::std::chrono::hh_mm_ss<Duration>::fractional_width;
```

## 约束说明

- 设D为common_type_t<Duration, seconds>::period::den。若1/D能用不超过18位十进制小数精确表示，值为所需的最小位数；否则为6。整秒精度对应0。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>

static_assert(asc::std::chrono::hh_mm_ss<asc::std::chrono::milliseconds>::fractional_width == 3);
static_assert(asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds>::fractional_width == 0);
```

## 关联API

- [`asc::std::chrono::hh_mm_ss`](chrono_hh_mm_ss.md)
- [本头文件的接口列表](asc_std_chrono.md)
