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

`asc::std::acos`计算反余弦，实数结果以弧度表示，取值范围为[0, π]。float重载可在Host侧和AI Core SIMT编程中调用，double和long double重载仅可在Host调用并保持对应精度；复数重载仅支持`complex<float>`。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
float acos(float value) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMT编程。

此原型对应头文件：`<asc/std/cmath>`。

### 原型2

```cpp
namespace asc::std {
double acos(double value) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host。

此原型对应头文件：`<asc/std/cmath>`。

### 原型3

```cpp
namespace asc::std {
long double acos(long double value) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host。

此原型对应头文件：`<asc/std/cmath>`。

### 原型4

```cpp
namespace asc::std {
template<class T> complex<T> acos(const complex<T>& value) noexcept;
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMT编程。

此原型对应头文件：`<asc/std/complex>`。

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为[-1, 1]。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为[-1, 1]。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为[-1, 1]。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数重载的实部与虚部浮点表示类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为[-1, 1]。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `float` | 以float精度返回反余弦弧度值。 |
| 原型2 | `double` | 以double精度返回反余弦弧度值。 |
| 原型3 | `long double` | 以平台long double精度返回反余弦弧度值。 |
| 原型4 | `complex<T>` | 返回复数反余弦的主值，T仅支持float。 |

## 约束说明

- float和`complex<float>`重载可在Host与AI Core SIMT编程中调用。
- double与long double重载限Host调用。
- 复数重载的T仅支持float。
- 实数有效定义域为[-1, 1]，域外输入和NaN的处理遵循对应数学后端。
- Host long double的实际精度由平台与工具链决定，不保证高于double。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

double example()
{
    return asc::std::acos(0.5);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
