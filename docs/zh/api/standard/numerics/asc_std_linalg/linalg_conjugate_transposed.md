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

`asc::std::linalg::conjugate_transposed` 创建共轭转置的非拥有多维视图。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

```cpp
template<class ElementType, class Extents, class Layout, class Accessor> [[nodiscard]] constexpr auto asc::std::linalg::conjugate_transposed(mdspan<ElementType, Extents, Layout, Accessor> input);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ElementType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
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

- 固定当前版本的 C++ 标准库公共入口的完整7实体合同：scaled/scaled_accessor、conjugated/conjugated_accessor、transposed/layout_transpose、conjugate_transposed
- 包括access/offset/nested accessor/factor、转换构造、算术类型共轭不变、ADL可共轭类型、双重共轭/转置消去、rank-2静态/动态extents交换、layout_left/right/stride与通用layout_transpose mapping全部观察/比较
- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段展示固定缓冲或多维视图的具体调用；底层存储须保持有效。

```cpp
#include <asc/std/linalg>
#include <asc/std/cstddef>

decltype(auto) example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, extents> view(values);
    return asc::std::linalg::conjugate_transposed(view);
}
```
