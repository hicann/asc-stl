# asc::host_mdspan

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

`asc::host_mdspan`使用host_accessor访问Host数据的mdspan别名。

## 声明

```cpp
namespace asc {
template <class Element, class Extents, class Layout = asc::std::layout_right,
    class Accessor = asc::std::default_accessor<Element>>
using host_mdspan = asc::std::mdspan<Element, Extents, Layout, asc::host_accessor<Accessor>>;
}  // namespace asc
```

## 约束说明

- Host访问器只解引用Host可访问的有效存储；不把设备指针转换成可在Host直接访问的存储。视图或访问器不拥有底层对象。


## 调用示例

以下片段选用具体模板实参展示别名类型。

```cpp
#include <asc/mdspan>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

void use_type()
{
    using selected = asc::host_mdspan<int, asc::std::extents<asc::std::size_t, 4>>;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
