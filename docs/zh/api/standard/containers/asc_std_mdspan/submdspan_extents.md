# asc::std::submdspan_extents

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

`asc::std::submdspan_extents` 计算整数索引与 full_extent 混合切片的结果维度，不访问元素存储。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
template<class Extents, class FirstIndex, class SecondIndex> constexpr auto asc::std::submdspan_extents(const Extents& extents, FirstIndex first_slice, SecondIndex second_slice);
```

### 原型 2

```cpp
template<class Extents, class Index> constexpr auto asc::std::submdspan_extents(const Extents& extents, Index first_slice, full_extent_t second_slice);
```

### 原型 3

```cpp
template<class Extents, class Index> constexpr auto asc::std::submdspan_extents(const Extents& extents, full_extent_t first_slice, Index second_slice);
```

### 原型 4

```cpp
template<class Extents, class Offset, class SliceExtent, class Stride> constexpr auto asc::std::submdspan_extents(const Extents& extents, const strided_slice<Offset, SliceExtent, Stride>& first_slice, full_extent_t second_slice);
```

### 原型 5

```cpp
template<class Extents, class Offset, class SliceExtent, class Stride> constexpr auto asc::std::submdspan_extents(const Extents& extents, full_extent_t first_slice, const strided_slice<Offset, SliceExtent, Stride>& second_slice);
```

### 原型 6

```cpp
template<class Extents, class Pair> constexpr auto asc::std::submdspan_extents(const Extents& extents, const Pair& first_slice, full_extent_t second_slice);
```

### 原型 7

```cpp
template<class Extents, class Pair> constexpr auto asc::std::submdspan_extents(const Extents& extents, full_extent_t first_slice, const Pair& second_slice);
```

### 原型 8

```cpp
template<class Extents> constexpr auto asc::std::submdspan_extents(const Extents& extents, full_extent_t first_slice, full_extent_t second_slice);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `FirstIndex` | 第一维切片下标的整数类型，须可转换为 index_type。 |
| `SecondIndex` | 第二维切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | 第一维的整数切片下标；结果维度中该维固定为该单一索引。 |
| `second_slice` | 输入 | 第二维的整数切片下标；结果维度中该维固定为该单一索引。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Index` | 切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | 第一维的整数切片下标；结果维度中该维固定为该单一索引。 |
| `second_slice` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Index` | 切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | asc::std::full_extent 标记；表示第一维整维保留在结果中。 |
| `second_slice` | 输入 | 第二维的整数切片下标；结果维度中该维固定为该单一索引。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Offset` | 第一维跨步切片的起始偏移类型（strided_slice::offset），须为整数类型。 |
| `SliceExtent` | 第一维跨步切片的长度类型（strided_slice::extent），须为整数类型。 |
| `Stride` | 第一维跨步切片的步长类型（strided_slice::stride），须为整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | 第一维的跨步切片描述（strided_slice：起始偏移、长度、步长）。 |
| `second_slice` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Offset` | 第二维跨步切片的起始偏移类型（strided_slice::offset），须为整数类型。 |
| `SliceExtent` | 第二维跨步切片的长度类型（strided_slice::extent），须为整数类型。 |
| `Stride` | 第二维跨步切片的步长类型（strided_slice::stride），须为整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | asc::std::full_extent 标记；表示第一维整维保留在结果中。 |
| `second_slice` | 输入 | 第二维的跨步切片描述（strided_slice：起始偏移、长度、步长）。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Pair` | 表示闭区间 [first, last] 的下标对类型，两个成员须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | 第一维的闭区间下标对 {first, last}；结果该维长度为 last - first + 1。 |
| `second_slice` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |
| `Pair` | 表示闭区间 [first, last] 的下标对类型，两个成员须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | asc::std::full_extent 标记；表示第一维整维保留在结果中。 |
| `second_slice` | 输入 | 第二维的闭区间下标对 {first, last}；结果该维长度为 last - first + 1。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 被切片的源维度描述类型（extents）；本组原型处理其前两维的切片。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `extents` | 输入 | 被切片的源维度描述对象；本组原型对其前两维应用切片。 |
| `first_slice` | 输入 | asc::std::full_extent 标记；表示第一维整维保留在结果中。 |
| `second_slice` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 2 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 3 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 4 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 5 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 6 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 7 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |
| 原型 8 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整submdspan家族：full_extent_t/full_extent、strided_slice及deduction guide、submdspan_mapping_result、submdspan_extents/submdspan_mapping/submdspan
- 全部有效整数降rank/full/pair-like/strided slice组合，零与任意rank、静态/动态/混合/空extent、layout_left/layout_right/layout_stride源及标准布局保持或layout_stride回退
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域
- 双索引重载仅在 FirstIndex 和 SecondIndex 均为整数时参与匹配
- full_extent、pair-like 与 strided_slice 使用各自的专门重载
- Index 必须为整数
- pair-like 与 strided_slice 切片由各自的专门重载处理
- Pair 切片须具有 first/second 成员或为恰有两个元素的 ASC-STL tuple-like 类型
- 整数索引由专门重载处理

## 调用示例

以下 Host C++ 片段展示整数索引与 full_extent 混合切片；设备侧须在 AI Core 函数内调用，索引须在各维度范围内。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

bool example()
{
    using extents_type = asc::std::extents<asc::std::size_t, 2, 3>;
    extents_type extents{};
    const auto row_extents = asc::std::submdspan_extents(extents, 1, asc::std::full_extent);
    const auto column_extents = asc::std::submdspan_extents(extents, asc::std::full_extent, 1);

    // 选取一行后保留3列，选取一列后保留2行。
    return row_extents.extent(0) == 3 && column_extents.extent(0) == 2;
}
```
