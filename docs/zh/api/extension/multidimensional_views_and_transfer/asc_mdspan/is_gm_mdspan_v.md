# asc::is_gm_mdspan_v

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

`asc::is_gm_mdspan_v`表示类型是否为使用GM访问器的mdspan。

## 声明

```cpp
namespace asc {
template<class T> inline constexpr bool is_gm_mdspan_v;
} // namespace asc
```

## 约束说明

- 提供Host和GM视图以及AI Core SIMD编程UB视图。
- 允许有符号步长。
- 可选的Host DLPack桥接不抛出异常。

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

inline constexpr auto example = asc::is_gm_mdspan_v<asc::gm_mdspan<int, asc::std::extents<asc::std::size_t, 4>>>;
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
