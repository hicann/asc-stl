# asc::std::chrono::year_month::`operator-=`

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

`asc::std::chrono::year_month::operator-=`按给定距离或操作数反向更新当前值。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::year_month`](chrono_year_month.md)。

### 原型1

```cpp
// asc::std::chrono::year_month 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr year_month& operator-=(const months& offset) noexcept;
```

### 原型2

```cpp
// asc::std::chrono::year_month 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr year_month& operator-=(const years& offset) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `offset` | 输入 | 待减去的有符号月数；负值等价于向后加月。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `offset` | 输入 | 待减去的有符号年数，单位为年；月份不变。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `year_month &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `year_month &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 月份偏移按12个月进位到年份；年份与结果字段须在各自可表示范围内。
- 运算及中间值必须可表示。

## 调用示例

以下Host片段以具体日期或时间类型演示调用；数值须满足本页约束。

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::year_month value = chrono::year_month{chrono::year{2024}, chrono::month{5}};
    value -= chrono::months{1};
    return static_cast<int>(value.year()) == 2024 && static_cast<unsigned>(value.month()) == 4;
}
```

## 关联API

- [`asc::std::chrono::year_month`](chrono_year_month.md)
- [本头文件的接口列表](asc_std_chrono.md)
