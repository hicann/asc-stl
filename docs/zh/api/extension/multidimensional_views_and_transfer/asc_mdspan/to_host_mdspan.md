# asc::to_host_mdspan

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

头文件路径为：`<asc/mdspan>`。

`asc::to_host_mdspan`从Host数据指针、范围和步长创建host_mdspan。

## 函数原型

```cpp
namespace asc {
template<class Element, asc::std::size_t Rank, class Layout = asc::layout_stride_relaxed> bool to_host_mdspan(const DLTensor& tensor, asc::host_mdspan<Element, asc::std::dextents<asc::std::size_t, Rank>, Layout>& output) noexcept;
} // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Element` | 视图所访问元素的类型；底层存储须包含相应有效对象。 |
| `Rank` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |
| `Layout` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tensor` | 输入 | 待转换或搬运的张量描述；数据指针、形状和步长须有效。 |
| `output` | 输出 | 提供非拥有多维数据视图；底层存储须在视图使用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 提供Host和GM视图以及AI Core SIMD编程UB视图。
- 允许有符号步长。
- 可选的Host DLPack桥接不抛出异常。

## 调用示例

DLPack桥接接口仅在提供DLPack头文件时可用；以下Host片段借用调用方管理的视图和张量存储。

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

#if __has_include(<dlpack/dlpack.h>)
decltype(auto) example(const DLTensor& tensor, asc::host_mdspan<int, asc::std::dextents<asc::std::size_t, 2>, asc::layout_stride_relaxed>& output)
{
    return asc::to_host_mdspan<int, 2>(tensor, output);
}
#endif
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
