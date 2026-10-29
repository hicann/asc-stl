# asc::std::chrono::abs

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

`asc::std::chrono::abs`返回时长的非负值。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

```cpp
namespace asc::std::chrono {
template<class Rep, class Period> [[nodiscard]] constexpr duration<Rep, Period> abs(duration<Rep, Period> value);
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep` | 输入时长的计数表示类型。 |
| `Period` | 输入时长一个计数单位对应的秒数，以ratio表示。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待取绝对值的时长；返回同一计时单位下的非负时长，计时单位由period决定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `duration<Rep, Period>` | 返回时长的非负值。 |

## 约束说明

- 仅当Rep的numeric_limits::is_signed为true时参与重载；无符号计数不参与。
- 结果必须能由Rep表示。有符号最小负值的正值不能表示时，不得调用。
- 不改变计时周期，返回与输入相同的duration类型。

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    return chrono::abs(chrono::seconds{-3}).count() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
