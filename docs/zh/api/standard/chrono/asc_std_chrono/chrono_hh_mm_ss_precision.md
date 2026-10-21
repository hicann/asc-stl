# asc::std::chrono::hh_mm_ss::precision

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

`hh_mm_ss<Duration>::precision`是时分秒分解所用的秒以下精度类型。它是duration，计数类型为`common_type_t<Duration, seconds>::rep`，周期为1 / 10^fractional_width秒。

fractional_width的计算规则见[`fractional_width`](chrono_hh_mm_ss_fractional_width.md)。

## 声明

precision是hh_mm_ss的公开成员类型；上述别名仅演示如何查询它。

```cpp
template<class Duration>
using hh_mm_ss_precision_t =
    typename asc::std::chrono::hh_mm_ss<Duration>::precision;
```

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using split_type = asc::std::chrono::hh_mm_ss<asc::std::chrono::milliseconds>;
static_assert(asc::std::is_same_v<typename split_type::precision, asc::std::chrono::milliseconds>);
```

## 关联API

- [`asc::std::chrono::hh_mm_ss`](chrono_hh_mm_ss.md)
- [本头文件的接口列表](asc_std_chrono.md)
