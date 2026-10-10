# asc::std::chrono::floor

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

`asc::std::chrono::floor` 把时长或时间点向负无穷方向转换为指定精度。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
template<class ToDuration, class Clock, class Duration> [[nodiscard]] constexpr time_point<Clock, ToDuration> asc::std::chrono::floor(const time_point<Clock, Duration>& value);
```

### 原型 2

```cpp
template<class ToDuration, class Re, class Period> [[nodiscard]] constexpr ToDuration asc::std::chrono::floor(const duration<Re, Period>& value);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Clock` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Duration` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ToDuration` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Re` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Period` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `time_point<Clock, ToDuration>` | 返回按所选精度和舍入规则转换后的时长或时间点。 |
| 原型 2 | `ToDuration` | 返回按所选精度和舍入规则转换后的时长或时间点。 |

## 约束说明

- 提供值运算以及六个显式关系运算符
- 支持用户定义时钟、值运算以及六个显式关系运算符

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/chrono>

decltype(auto) example()
{
    asc::std::chrono::milliseconds value{1500};
    return asc::std::chrono::floor<asc::std::chrono::seconds>(value);
}
```
