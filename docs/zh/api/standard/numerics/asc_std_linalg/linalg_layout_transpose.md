# asc::std::linalg::layout_transpose

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

`asc::std::linalg::layout_transpose`按指定布局把多维索引映射为底层存储偏移。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 声明

```cpp
namespace asc::std::linalg {
template<class Layout> class layout_transpose;
} // namespace asc::std::linalg
```

## 约束说明

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>
#include <asc/std/type_traits>

bool example()
{
    using Layout = asc::std::linalg::layout_transpose<asc::std::layout_right>;
    using Extents = asc::std::extents<int, 3, 2>;
    using NestedExtents = asc::std::extents<int, 2, 3>;
    asc::std::layout_right::mapping<NestedExtents> original;
    Layout::mapping<Extents> transposed(original);
    static_assert(asc::std::is_same_v<Layout::nested_layout_type, asc::std::layout_right>);
    return transposed(2, 1) == original(1, 2);
}
```

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
