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
| `Element` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Extents` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Layout` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Accessor` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `view` | 输入 | 提供非拥有多维数据视图；底层存储须在视图使用期间有效。 |
| `device_type` | 输入 | 目标设备的类型标识，用于构造兼容的张量描述。 |
| `device_id` | 输入 | 指定“把兼容的 mdspan 视图转换为 DLPack 张量描述”使用的标量值；取值须满足声明和约束。 |
| `output` | 输出 | 提供“把兼容的 mdspan 视图转换为 DLPack 张量描述”使用的对象引用；被引用对象须在调用期间有效。 |

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
