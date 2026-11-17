# asc::std::linalg::conjugate_transposed

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

头文件路径为：`<asc/std/linalg>`。

`asc::std::linalg::conjugate_transposed`创建共轭转置的非拥有多维视图。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

```cpp
namespace asc::std::linalg {
template<class ElementType, class Extents, class Layout, class Accessor> constexpr auto conjugate_transposed(mdspan<ElementType, Extents, Layout, Accessor> input);
} // namespace asc::std::linalg
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ElementType` | 视图访问的元素类型，决定读取、变换和返回值的类型。 |
| `Extents` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Layout` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Accessor` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 提供非拥有多维数据视图；底层存储须在视图使用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 返回共轭转置的非拥有多维视图。 |

## 约束说明

- 转置仅适用于rank为2的矩阵视图或映射；两个维度和对应步长互换，不提供任意阶轴重排。

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例计算两个传感器、两个采样时刻的复数协方差 `R = AᴴA / 2`。`scaled`与`conjugate_transposed`组合消除了显式共轭转置临时矩阵；矩阵乘法的归约循环仍由调用方实现。输入未中心化，因此此处为零均值信号的协方差（一般信号的二阶矩）。

```cpp
#include <asc/std/linalg>

bool example()
{
    using Complex = asc::std::complex<float>;
    Complex values[4] = {{1.0f, 1.0f}, {2.0f, 0.0f}, {0.0f, 0.0f}, {1.0f, -1.0f}};
    using E = asc::std::extents<int, 2, 2>;
    asc::std::mdspan<Complex, E> samples(values);
    // 归一化共轭转置是借用视图，values须在整个归约期间有效。
    const auto adjoint = asc::std::linalg::scaled(
        0.5f, asc::std::linalg::conjugate_transposed(samples));
    Complex covariance[4]{};
    for (int j = 0; j < 2; ++j) {
        for (int k = 0; k < 2; ++k) {
            for (int r = 0; r < 2; ++r) {
                covariance[j * 2 + k] += adjoint(j, r) * samples(r, k);
            }
        }
    }
    return covariance[0] == Complex(1.0f, 0.0f) &&
        covariance[1] == Complex(1.0f, -1.0f) &&
        covariance[2] == Complex(1.0f, 1.0f) &&
        covariance[3] == Complex(3.0f, 0.0f) && values[0] == Complex(1.0f, 1.0f);
}
```

本例使用`complex<float>`及只读视图访问。返回的视图不会复制输入，也不会修改底层元素；同时修改输入会影响后续读取。此Host示例不承诺任意复数类型或访问器的设备支持。

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
