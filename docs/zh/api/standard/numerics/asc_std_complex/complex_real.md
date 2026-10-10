# asc::std::complex::real

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

头文件路径为：`<asc/std/complex>`。

`asc::std::complex::real` 返回复数实部。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] value_type asc::std::complex::real() const volatile;
```

### 原型 2

```cpp
[[nodiscard]] constexpr value_type asc::std::complex::real() const;
```

### 原型 3

```cpp
void asc::std::complex::real(value_type value) volatile;
```

### 原型 4

```cpp
constexpr void asc::std::complex::real(value_type value);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `value_type` | 返回复数实部。 |
| 原型 2 | `value_type` | 返回复数实部。 |
| 原型 3 | `void` | 无返回值。 |
| 原型 4 | `void` | 无返回值。 |

## 约束说明

- 仅提供页面声明的 float 或 complex<float> 运算
- 接口可用性取决于相应的 float 数学能力

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/complex>

void example(asc::std::complex<float>& object)
{
    (void)object.real();
}
```
