# asc::std::chrono::month_weekday::month_weekday

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

`asc::std::chrono::month_weekday::month_weekday`按本页所列构造形态初始化`month_weekday`对象。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型1

```cpp
constexpr month_weekday();
```

### 原型2

```cpp
constexpr month_weekday(const chrono::month& month_value, const chrono::weekday_indexed& weekday_value) noexcept;
```

### 原型3

```cpp
constexpr month_weekday(const month_weekday& month_value);
```

### 原型4

```cpp
constexpr month_weekday(month_weekday&& month_value);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入 | 月份值，1到12表示一月至十二月。 |
| `weekday_value` | 输入 | 带序号的星期几描述（weekday_indexed），指定该月的第几个星期几。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入 | 用于复制构造的month_weekday对象。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入/输出 | 用于移动构造的month_weekday对象；移动后源对象处于有效但未指定状态。 |

## 返回值说明

无返回值。

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::month_weekday value{asc::std::chrono::month{2}, asc::std::chrono::weekday_indexed{asc::std::chrono::weekday{4}, 4}};
    return value.weekday_indexed().index() == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
