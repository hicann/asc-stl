# asc::std::literals::chrono_literals::operator""us

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

`operator""us` 以字面量数值构造 `chrono::microseconds`，整型与浮点字面量均受支持。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

### 原型 1

```cpp
asc::std::chrono::microseconds asc::std::literals::chrono_literals::operator""us(unsigned long long arg)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 2

```cpp
asc::std::chrono::microseconds asc::std::literals::chrono_literals::operator""us(long double arg)
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `arg` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::chrono::microseconds` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 整数字面量按目标表示精确转换
- 浮点字面量截断到目标表示的 tick 数

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/chrono>

decltype(auto) example(unsigned long long arg)
{
    return asc::std::literals::chrono_literals::operator""us(arg);
}
```
