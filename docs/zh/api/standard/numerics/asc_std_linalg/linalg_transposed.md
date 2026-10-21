# asc::std::linalg::transposed

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

`asc::std::linalg::transposed`创建交换维度顺序的非拥有多维视图。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

```cpp
namespace asc::std::linalg {
template<class ElementType, class Extents, class Layout, class Accessor> constexpr auto transposed(mdspan<ElementType, Extents, Layout, Accessor> input);
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
| `auto` | 返回交换维度顺序的非拥有多维视图。 |

## 约束说明

- 转置仅适用于rank为2的矩阵视图或映射；两个维度和对应步长互换，不提供任意阶轴重排。

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并在对象与底层存储仍有效时检查结果。

```cpp
#include <asc/std/linalg>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using E = asc::std::extents<int, 2, 3>;
    asc::std::mdspan<int, E> view(values);
    const auto result = asc::std::linalg::transposed(view);
    return result.extent(0) == 3 && result.extent(1) == 2 &&
        result.accessor().access(result.data_handle(), result.mapping()(2, 1)) == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
