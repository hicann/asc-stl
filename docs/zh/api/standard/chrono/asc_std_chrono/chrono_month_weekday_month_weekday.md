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

`asc::std::chrono::month_weekday::month_weekday` 按本页所列构造形态初始化 `month_weekday` 对象。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
constexpr month_weekday();
```

### 原型 2

```cpp
constexpr month_weekday(const chrono::month& month_value, const chrono::weekday_indexed& weekday_value) noexcept;
```

### 原型 3

```cpp
constexpr month_weekday(const month_weekday& month_value);
```

### 原型 4

```cpp
constexpr month_weekday(month_weekday&& month_value);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入 | 月份值，1 到 12 表示一月至十二月。 |
| `weekday_value` | 输入 | 带序号的星期几描述（weekday_indexed），指定该月的第几个星期几。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入 | 用于复制构造的 month_weekday 对象。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `month_value` | 输入/输出 | 用于移动构造的 month_weekday 对象；移动后源对象处于有效但未指定状态。 |

## 约束说明

- 纯日历/组合/别名/字面量为Host、AI Core SIMD 编程 和 AI Core SIMT 编程
- system_clock仅为sys_time精确形状提供类型、rep/period/duration/time_point和is_steady类型

## 调用示例

以下 Host 片段以具体日期或时间类型演示调用；数值须满足本页约束。

```cpp
#include <asc/std/chrono>

void example()
{
    asc::std::chrono::month_weekday value{};
    (void)value;
}
```
