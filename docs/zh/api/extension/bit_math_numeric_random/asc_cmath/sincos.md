# asc::sincos

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

头文件路径为：`<asc/cmath>`。

`asc::sincos` 在一次调用中计算输入值的正弦和余弦，并分别写入两个输出指针。

## 函数原型

### 原型 1

```cpp
void asc::sincos(float value, float* sin_out, float* cos_out) noexcept;
```

### 原型 2

```cpp
void asc::sincos(double value, double* sin_out, double* cos_out) noexcept;
```

### 原型 3

```cpp
void asc::sincos(long double value, long double* sin_out, long double* cos_out) noexcept;
```

### 原型 4

```cpp
template<class T> void asc::sincos(T value, double* sin_out, double* cos_out) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算正弦和余弦的整数值；内部转换为 double 后计算。 || `sin_out` | 输出 | 输出参数，接收输入值的正弦计算结果；指针须有效（指向可写 `float`）。 |
| `cos_out` | 输出 | 输出参数，接收输入值的余弦计算结果；指针须有效（指向可写 `float`）。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算正弦和余弦的整数值；内部转换为 double 后计算。 || `sin_out` | 输出 | 输出参数，接收输入值的正弦计算结果；指针须有效（指向可写 `double`）。 |
| `cos_out` | 输出 | 输出参数，接收输入值的余弦计算结果；指针须有效（指向可写 `double`）。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算正弦和余弦的整数值；内部转换为 double 后计算。 || `sin_out` | 输出 | 输出参数，接收输入值的正弦计算结果；指针须有效（指向可写 `long double`）。 |
| `cos_out` | 输出 | 输出参数，接收输入值的余弦计算结果；指针须有效（指向可写 `long double`）。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 整型输入值的类型；须为整数或枚举类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算正弦和余弦的整数值；内部转换为 double 后计算。 || `sin_out` | 输出 | 输出参数，接收输入值的正弦计算结果；指针须有效（指向可写 `double`）。 |
| `cos_out` | 输出 | 输出参数，接收输入值的余弦计算结果；指针须有效（指向可写 `double`）。 |

## 返回值说明

无返回值。

## 约束说明

- sin_out 和 cos_out 不得为空
- float 重载可在 Host 和 AI Core SIMT 编程中调用，其余重载仅可在 Host 调用
- 模板重载要求 T 为整数或枚举类型

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/cmath>

void example(float value, float* sin_out, float* cos_out)
{
    asc::sincos(value, sin_out, cos_out);
}
```
