# asc::std::literals::complex_literals::operator""if

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

`operator""if`以纯虚数字面量构造`complex<float>`，等价于`complex<float>{0.0f, static_cast<float>(arg)}`。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1

```cpp
// asc::std::literals::complex_literals 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr asc::std::complex<float> operator""if(long double arg) noexcept;
```

该原型适用于`C++17+`，可用位置为Host。

### 原型2

```cpp
// asc::std::literals::complex_literals 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr asc::std::complex<float> operator""if(unsigned long long arg) noexcept;
```

该原型适用于`C++17+`，可用位置为Host。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `arg` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::complex<float>` | 实部为0、虚部为字面量数值的float复数。 |

## 约束说明

- 虚部取字面量数值转换到float的结果，实部为零。
- 整数字面量先转换为float再作为虚部，实部为零。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/complex>

decltype(auto) example(long double arg)
{
    return asc::std::literals::complex_literals::operator""if(arg);
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
