# asc::std::acos（函数）

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

头文件路径为：`<asc/std/cmath>`、`<asc/std/complex>`。

`asc::std::acos` 计算反余弦，实数结果以弧度表示，取值范围为 [0, π]。float 重载可在 Host 侧和 AI Core SIMT 编程中调用，double 和 long double 重载仅可在 Host 调用并保持对应精度；复数重载仅支持 complex<float>。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

### 原型 1

```cpp
float asc::std::acos(float value) noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMT 编程。

此原型对应头文件：`<asc/std/cmath>`。

### 原型 2

```cpp
double asc::std::acos(double value) noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host。

此原型对应头文件：`<asc/std/cmath>`。

### 原型 3

```cpp
long double asc::std::acos(long double value) noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host。

此原型对应头文件：`<asc/std/cmath>`。

### 原型 4

```cpp
template<class T> complex<T> asc::std::acos(const complex<T>& value) noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMT 编程。

此原型对应头文件：`<asc/std/complex>`。

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为 [-1, 1]。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为 [-1, 1]。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为 [-1, 1]。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为 [-1, 1]。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `float` | 以 float 精度返回反余弦弧度值。 |
| 原型 2 | `double` | 以 double 精度返回反余弦弧度值。 |
| 原型 3 | `long double` | 以平台 long double 精度返回反余弦弧度值。 |
| 原型 4 | `complex<T>` | 返回复数反余弦的主值，T 仅支持 float。 |

## 约束说明

- float 和 complex<float> 重载可在 Host 与 AI Core SIMT 编程中调用
- double 与 long double 重载限 Host 调用
- 复数重载的 T 仅支持 float
- 实数有效定义域为 [-1, 1]，域外输入和 NaN 的处理遵循对应数学后端
- Host long double 的实际精度由平台与工具链决定，不保证高于 double

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

double example()
{
    return asc::std::acos(0.5);
}
```
