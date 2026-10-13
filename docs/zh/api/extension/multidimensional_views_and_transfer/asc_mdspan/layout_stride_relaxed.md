# asc::layout_stride_relaxed

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

`asc::layout_stride_relaxed`提供允许宽松步长约束的mdspan布局映射策略。

## 声明

```cpp
namespace asc {
struct layout_stride_relaxed;
} // namespace asc
```

## 约束说明

- 提供Host和GM视图以及AI Core SIMD编程UB视图。
- 允许有符号步长。
- 可选的Host DLPack桥接不抛出异常。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/mdspan>
#include <asc/std/mdspan>

bool example()
{
    using Extents = asc::std::extents<int, 2, 3>;
    asc::dstrides<asc::std::ptrdiff_t, 2> strides(5, 1);
    asc::layout_stride_relaxed::mapping<Extents> mapping(Extents{}, strides);
    return mapping(1, 2) == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
