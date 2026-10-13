# asc::std::chrono::time_point::`operator--`

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

`asc::std::chrono::time_point::operator--`把当前迭代器或计数值后退一步。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

所属类型：[`asc::std::chrono::time_point`](chrono_time_point.md)。

### 原型1

```cpp
// asc::std::chrono::time_point 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr time_point<Clock, Duration>& operator--();
```

### 原型2

```cpp
// asc::std::chrono::time_point 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr time_point<Clock, Duration> operator--(int unused);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `unused` | 输入 | 用于区分后置自增或后置自减形式的占位参数；调用时写作整数0。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `time_point<Clock, Duration> &` | 返回更新后的当前对象引用。 |
| 原型2 | `time_point<Clock, Duration>` | 返回更新后的迭代器或计数值。 |

## 约束说明

- 支持用户定义时钟、值运算以及六个显式关系运算符。

## 调用示例

以下Host片段以具体日期或时间类型演示调用；数值须满足本页约束。

```cpp
#include <asc/std/chrono>

void example(asc::std::chrono::time_point<asc::std::chrono::system_clock>& value)
{
    --value;
}
```

## 关联API

- [`asc::std::chrono::time_point`](chrono_time_point.md)
- [本头文件的接口列表](asc_std_chrono.md)
