# asc::to_dlpack_tensor

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

`asc::to_dlpack_tensor` 把兼容的 mdspan 视图转换为 DLPack 张量描述。

## 函数原型

```cpp
template<class Element, class Extents, class Layout, class Accessor> bool asc::to_dlpack_tensor(const asc::std::mdspan<Element, Extents, Layout, Accessor>& view, DLDeviceType device_type, int device_id, asc::dlpack_tensor<Extents::rank()>& output) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Element` | 视图的元素类型；须属于 DLPack 桥接支持的元素类型集合，否则转换返回 false。 |
| `Extents` | 视图的维度说明类型；其 rank() 决定输出张量的秩。 |
| `Layout` | 视图的布局映射类型；其逐维步长被写入输出张量的步长数组。 |
| `Accessor` | 视图的访问器类型；随 mdspan 一并参与推导，不改变转换结果。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `view` | 输入 | 被转换的 mdspan 视图（非拥有）；其数据指针须非空，否则返回 false。转换仅借用其数据地址，不获得存储所有权。 |
| `device_type` | 输入 | 输出张量记录的设备类型（DLDeviceType 枚举值）；仅接受 kDLCPU 与 kDLExtDev，其它取值返回 false。 |
| `device_id` | 输入 | 输出张量记录的设备编号（int），原样写入其设备描述，不做校验。 |
| `output` | 输出 | 接收 DLPack 张量描述的输出对象（dlpack_tensor<Extents::rank()>）；成功时写入数据指针、设备、维数、dtype 及逐维形状与步长（byte_offset 置 0），失败时不改动。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 提供 Host 和 GM 视图以及 AI Core SIMD 编程 UB 视图
- 允许有符号步长
- 可选的 Host DLPack 桥接不抛出异常

## 调用示例

DLPack 桥接接口仅在提供 DLPack 头文件时可用；以下 Host 片段借用调用方管理的视图和张量存储。

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
decltype(auto) example(const asc::host_mdspan<int, asc::std::dextents<asc::std::size_t, 2>, asc::layout_stride_relaxed>& view, asc::dlpack_tensor<2>& output)
{
    return asc::to_dlpack_tensor(view, kDLCPU, 0, output);
}
#endif
```
