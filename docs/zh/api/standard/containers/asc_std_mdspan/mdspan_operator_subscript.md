# asc::std::mdspan::operator[]

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

`asc::std::mdspan::operator[]` 在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
template<class ...Indices> constexpr reference asc::std::mdspan::operator[](Indices... indices) const noexcept requires (Extents::rank() == 1&& sizeof...(Indices) == 1);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 2

```cpp
template<class ...Indices> constexpr reference asc::std::mdspan::operator[](Indices... indices) const noexcept requires (Extents::rank() > 1&& sizeof...(Indices) == Extents::rank());
```

该原型适用于 `C++23+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 3

```cpp
template<class OtherIndexType> constexpr reference asc::std::mdspan::operator[](const array<OtherIndexType, Extents::rank()>& indices) const noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 4

```cpp
template<class OtherIndexType> constexpr reference asc::std::mdspan::operator[](span<OtherIndexType, Extents::rank()> indices) const noexcept;
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Indices` | 下标实参的类型包；仅含一个成员，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 元素下标；适用于秩为 1 的视图，须满足 0 <= 下标 < extent(0)，本接口不检查越界。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Indices` | 按维度顺序排列的下标类型包；个数须等于秩，各类型须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序给出的元素下标包；个数须等于秩，每个下标须落在对应维长度范围内，本接口不检查越界。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | array 中下标的类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序存放各维下标的 array；长度须等于秩，各下标须落在对应维长度范围内，本接口不检查越界。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | span 中下标的类型，须可转换为 index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序存放各维下标的 span；长度须等于秩，各下标须落在对应维长度范围内，本接口不检查越界。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 3 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型 4 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- 仅提供一维标量下标访问，索引必须处于有效范围内
- 提供多维标量下标语法
- 索引数量和每一维取值必须与 extents 相容
- 遵循 span 的静态或动态 extent、指针和连续范围构造约束
- AI Core SIMD 编程 仅支持地址空间相容的普通指针表示

## 调用示例

以下 Host 片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

decltype(auto) example(const asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 4>, asc::std::layout_right, asc::std::default_accessor<int>>& view)
{
    return view[0];
}
```
