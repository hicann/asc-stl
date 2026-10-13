# asc::std::complex::`operator-=`

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

`asc::std::complex::operator-=`按给定距离或操作数反向更新当前值。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

所属类型：[`asc::std::complex`](complex.md)。

### 原型1

```cpp
// asc::std::complex 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr complex<T>& operator-=(const T& rhs) noexcept;
```

### 原型2

```cpp
// asc::std::complex 类内的声明节选；模板形参和其他成员由所属类提供。
template<class U> constexpr complex<T>& operator-=(const complex<U>& rhs) noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `rhs` | 输入 | 减法赋值的右操作数（实数标量，从当前对象的实部减去）。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 右操作数复数的成分（实部与虚部）值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `rhs` | 输入 | 减法赋值的右操作数（复数，实部与虚部分别从当前对象减去）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型2 | `complex<T> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/complex>

void example(asc::std::complex<float>& value)
{
    value -= 2.0f;
}
```

## 关联API

- [`asc::std::complex`](complex.md)
- [本头文件的接口列表](asc_std_complex.md)
