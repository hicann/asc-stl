# asc::std::dims

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

头文件路径为：`<asc/std/mdspan>`。

`asc::std::dims`按指定维度数构造运行期维度长度类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
namespace asc::std {
template<size_t Rank, class IndexType = size_t>
using dims = dextents<IndexType, Rank>;
}
```

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

using shape_type = asc::std::dims<2>;
static_assert(asc::std::is_same_v<shape_type::index_type, asc::std::size_t>);
static_assert(shape_type::rank_dynamic() == 2);

bool example()
{
    const shape_type shape(2, 3);
    return shape.extent(0) == 2 && shape.extent(1) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
