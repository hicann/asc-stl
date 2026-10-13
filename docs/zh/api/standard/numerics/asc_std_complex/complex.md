# asc::std::complex

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

`asc::std::complex`保存实部和虚部并提供复数算术操作。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 声明

```cpp
namespace asc::std {
template<class T> class complex;
} // namespace asc::std
```

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> left(1.0F, 2.0F);
    asc::std::complex<float> right(3.0F, 4.0F);
    const auto product = left * right;
    return product.real() == -5.0F && product.imag() == 10.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
