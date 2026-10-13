# asc::std::submdspan_mapping

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

`asc::std::submdspan_mapping` 计算混合切片的映射与起始偏移，不拥有底层存储。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
template<class Mapping, class FirstIndex, class SecondIndex> constexpr auto asc::std::submdspan_mapping(const Mapping& source, FirstIndex first_index, SecondIndex second_index);
```

### 原型 2

```cpp
template<class Mapping, class Index> constexpr auto asc::std::submdspan_mapping(const Mapping& source, Index first_index, full_extent_t second_index);
```

### 原型 3

```cpp
template<class Mapping, class Index> constexpr auto asc::std::submdspan_mapping(const Mapping& source, full_extent_t first_index, Index second_index);
```

### 原型 4

```cpp
template<class Mapping, class Offset, class SliceExtent, class Stride> constexpr auto asc::std::submdspan_mapping(const Mapping& source, const strided_slice<Offset, SliceExtent, Stride>& first_index, full_extent_t second_index);
```

### 原型 5

```cpp
template<class Mapping, class Offset, class SliceExtent, class Stride> constexpr auto asc::std::submdspan_mapping(const Mapping& source, full_extent_t first_index, const strided_slice<Offset, SliceExtent, Stride>& second_index);
```

### 原型 6

```cpp
template<class Mapping, class Pair> constexpr auto asc::std::submdspan_mapping(const Mapping& source, const Pair& first_index, full_extent_t second_index);
```

### 原型 7

```cpp
template<class Mapping, class Pair> constexpr auto asc::std::submdspan_mapping(const Mapping& source, full_extent_t first_index, const Pair& second_index);
```

### 原型 8

```cpp
template<class Mapping> constexpr auto asc::std::submdspan_mapping(const Mapping& source);
```

### 原型 9

```cpp
template<class Mapping> constexpr auto asc::std::submdspan_mapping(const Mapping& source, full_extent_t first_index, full_extent_t second_index);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `FirstIndex` | 第一维切片下标的整数类型，须可转换为 index_type。 |
| `SecondIndex` | 第二维切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Index` | 切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Index` | 切片下标的整数类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Offset` | 第一维跨步切片的起始偏移类型（strided_slice::offset），须为整数类型。 |
| `SliceExtent` | 第一维跨步切片的长度类型（strided_slice::extent），须为整数类型。 |
| `Stride` | 第一维跨步切片的步长类型（strided_slice::stride），须为整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Offset` | 第二维跨步切片的起始偏移类型（strided_slice::offset），须为整数类型。 |
| `SliceExtent` | 第二维跨步切片的长度类型（strided_slice::extent），须为整数类型。 |
| `Stride` | 第二维跨步切片的步长类型（strided_slice::stride），须为整数类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | 提供“计算混合切片的映射与起始偏移，不拥有底层存储”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Pair` | 表示闭区间 [first, last] 的下标对类型，两个成员须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |
| `Pair` | 表示闭区间 [first, last] 的下标对类型，两个成员须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | 提供按位置访问或组合的元素集合。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mapping` | 源视图的布局映射类型（含维度信息），如 layout_right::mapping。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源数据或源对象。本调用为同步的编译期映射计算，source 被同步读取，调用期间有效即可。 |
| `first_index` | 输入 | 输入范围的起始迭代器或指针。 |
| `second_index` | 输入 | asc::std::full_extent 标记；表示第二维整维保留在结果中。 |

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
| 原型 9 | `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |

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
    asc::std::layout_right::mapping<extents_type> mapping(extents);
    const auto row = asc::std::submdspan_mapping(mapping, 1, asc::std::full_extent);
    const auto column = asc::std::submdspan_mapping(mapping, asc::std::full_extent, 1);

    // layout_right下第2行从偏移3开始，第2列从偏移1开始。
    return row.offset == 3 && column.offset == 1;
}
```
