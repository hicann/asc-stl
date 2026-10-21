# asc::std::mdspan::`operator[]`

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

`asc::std::mdspan::operator[]`在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`asc::std::mdspan`](mdspan.md)。

### 原型1

```cpp
// 一维调用的类内声明摘要，省略内部SFINAE。
// rank()==1，OtherIndexType须可转换且可不抛出异常地构造index_type。
template<class OtherIndexType>
constexpr reference operator[](OtherIndexType index) const;
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
// 多维调用的类内声明摘要，省略内部SFINAE。
// 下标数量须等于rank()，各下标须可转换为index_type。
template<class... OtherIndexTypes>
[[nodiscard]] constexpr reference operator[](OtherIndexTypes... indices) const;
```

仅在语言模式高于C++20且编译器定义`__cpp_multidimensional_subscript >= 202110L`时提供；C++17和C++20可使用一维标量或`array`/`span`下标形式。

### 原型3

```cpp
// asc::std::mdspan 类内的声明节选；模板形参和其他成员由所属类提供。
template<class OtherIndexType> constexpr reference operator[](const array<OtherIndexType, Extents::rank()>& indices) const;
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型4

```cpp
// asc::std::mdspan 类内的声明节选；模板形参和其他成员由所属类提供。
template<class OtherIndexType> constexpr reference operator[](span<OtherIndexType, Extents::rank()> indices) const;
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 一维下标实参的类型，须可转换为`index_type`且可不抛出异常地构造该类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 元素下标；适用于秩为1的视图，须满足0 <= 下标 < extent(0)，越界违反调用前提；可选调试断言不构成边界检查保证。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 按维度顺序排列的下标类型包；个数须等于秩，各类型须可转换为`index_type`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序给出的元素下标包；个数须等于秩，每个下标须落在对应维长度范围内，越界违反调用前提；可选调试断言不构成边界检查保证。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | `array`中下标的类型，须可转换为`index_type`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序存放各维下标的`array`；长度须等于秩，各下标须落在对应维长度范围内，越界违反调用前提；可选调试断言不构成边界检查保证。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | `span`中下标的类型，须可转换为`index_type`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 按维度顺序存放各维下标的`span`；长度须等于秩，各下标须落在对应维长度范围内，越界违反调用前提；可选调试断言不构成边界检查保证。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型2 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型3 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型4 | `reference` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- 未启用多维下标特性时，一维标量形式从C++17起提供，要求`rank()`==1。
- 启用多维下标特性时，变参标量形式要求下标个数等于`rank()`，也处理一维调用。
- `array`与固定extent的`span`形式均从C++17起提供；容器长度等于`rank()`。
- 每个下标须可转换且可不抛出异常地构造`index_type`，并处于对应维度的有效范围。
- 数据句柄及地址空间由`Accessor`决定；此接口不额外进行GM/UB指针转换。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

decltype(auto) example(const asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 4>, asc::std::layout_right, asc::std::default_accessor<int>>& view)
{
    return view[0];
}
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
