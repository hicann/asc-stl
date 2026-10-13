# asc::std::chrono::duration_cast

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

`asc::std::chrono::duration_cast`在指定时长类型之间转换计数与周期。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Rep, class Period> [[nodiscard]] constexpr ToDuration duration_cast(const duration<Rep, Period>& value);
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 转换结果的duration类型，决定结果计数表示和计时单位。 |
| `Rep` | 输入时长的计数表示类型。 |
| `Period` | 输入时长一个计数单位对应的秒数，以ratio表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待转换的时长；无法精确表示时向零截断。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `ToDuration` | 返回按所选精度和舍入规则转换后的时长或时间点。 |

## 约束说明

- 提供值运算以及六个显式关系运算符。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/chrono>

decltype(auto) example()
{
    asc::std::chrono::milliseconds value{1500};
    return asc::std::chrono::duration_cast<asc::std::chrono::seconds>(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
