# asc::std::linalg::scaled

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

`asc::std::linalg::scaled`创建按标量缩放元素的非拥有多维视图。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

以下返回类型通过访问器的公共成员类型表达；`add_const_t`与头文件中的返回类型等价。

```cpp
namespace asc::std::linalg {
template<class ScalingFactor, class Element, class Extents, class Layout, class Accessor>
constexpr mdspan<add_const_t<typename scaled_accessor<ScalingFactor, Accessor>::element_type>,
    Extents, Layout, scaled_accessor<ScalingFactor, Accessor>>
scaled(ScalingFactor scaling_factor, mdspan<Element, Extents, Layout, Accessor> input);
} // namespace asc::std::linalg
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ScalingFactor` | 缩放因子的类型；须可与元素值相乘。 |
| `Element` | 底层多维视图的元素类型。 |
| `Extents` | 底层多维视图的维度类型。 |
| `Layout` | 底层多维视图的布局类型。 |
| `Accessor` | 底层多维视图的访问器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `scaling_factor` | 输入 | 标量缩放因子；视图中每个元素按该因子缩放后读取。 |
| `input` | 输入 | 提供非拥有多维数据视图；底层存储须在视图使用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `mdspan<add_const_t<typename scaled_accessor<ScalingFactor, Accessor>::element_type>, Extents, Layout, scaled_accessor<ScalingFactor, Accessor>>` | 返回按标量缩放元素的非拥有多维视图。 |

## 约束说明

- 缩放因子须能与底层元素类型相乘；结果类型由乘法表达式确定。
- 返回视图借用`input`的存储，复制映射和缩放访问器；底层存储须在返回视图使用期间保持有效。
- 读取通过缩放访问器计算结果，不修改底层元素；Device使用还要求底层访问器、存储地址空间和乘法运算支持对应编程模式。

## 调用示例

以下Host示例给出具体输入，并检查结果。

```cpp
#include <asc/std/linalg>
#include <asc/std/cstddef>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    const auto scaled = asc::std::linalg::scaled(2, view);
    // 在values仍有效时读取借用视图，不将视图返回到数组生命周期之外。
    return scaled(1, 2) == 12 && values[5] == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
