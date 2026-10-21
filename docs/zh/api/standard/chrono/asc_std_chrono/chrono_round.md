# asc::std::chrono::round

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

`asc::std::chrono::round`按最接近且中点取偶规则转换时长或时间点精度。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Clock, class Duration> [[nodiscard]] constexpr time_point<Clock, ToDuration> round(const time_point<Clock, Duration>& value);
} // namespace asc::std::chrono
```

### 原型2

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Rep, class Period> [[nodiscard]] constexpr ToDuration round(const duration<Rep, Period>& value);
} // namespace asc::std::chrono
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 转换到的目标时长类型。 |
| `Clock` | 时间点所属的时钟类型，如system_clock。 |
| `Duration` | 源时间点的时长类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待四舍五入转换的时间点；恰在半途时向偶数取整。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 转换结果的duration类型，决定结果计数表示和计时单位。 |
| `Rep` | 输入时长的计数表示类型。 |
| `Period` | 输入时长一个计数单位对应的秒数，以ratio表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待四舍五入转换的时长；恰在半途时向偶数取整。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `time_point<Clock, ToDuration>` | 返回按所选精度和舍入规则转换后的时长或时间点。 |
| 原型2 | `ToDuration` | 返回按所选精度和舍入规则转换后的时长或时间点。 |

## 约束说明

- ToDuration须为duration，且其计数支持整数奇偶判定；内建浮点计数不适用。
- 两个最近候选距离相同时选择计数为偶数的候选；输入和候选结果均须可表示。
- 时间点形式对time_since_epoch()使用同一规则，并保留Clock。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/chrono>

decltype(auto) example()
{
    asc::std::chrono::milliseconds value{1500};
    return asc::std::chrono::round<asc::std::chrono::seconds>(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
