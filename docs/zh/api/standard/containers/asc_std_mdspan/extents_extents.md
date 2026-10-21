# asc::std::extents::extents

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

`asc::std::extents::extents`按本页所列构造形态初始化`extents`对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`extents<IndexType, Extents...>`](extents.md)。以下按互斥参与条件列声明摘要，省略仅供SFINAE的选择参数；所有列出构造均为`noexcept`。

### 原型1

```cpp
constexpr extents() noexcept = default;
```

静态维由模板实参固定，动态维默认置0。

### 原型2

```cpp
template<class... OtherIndexTypes>
explicit constexpr extents(OtherIndexTypes... dynvals) noexcept;
```

实参数量须为`rank_dynamic()`或`rank()`；各实参须可转换且可不抛出异常地构造`index_type`。

### 原型3

```cpp
template<class OtherIndexType, size_t Size>
constexpr extents(const array<OtherIndexType, Size>& exts) noexcept;
```

`Size`==`rank_dynamic()`时采用本非显式分支；元素须可转换且可不抛出异常地构造`index_type`。

### 原型4

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr extents(const array<OtherIndexType, Size>& exts) noexcept;
```

`Size`==`rank()`且`Size`!=`rank_dynamic()`时采用本显式分支；元素条件与上一原型相同。

### 原型5

```cpp
template<class OtherIndexType, size_t Size>
constexpr extents(span<OtherIndexType, Size> exts) noexcept;
```

`Size`==`rank_dynamic()`时采用本非显式分支；元素条件与`array`形式相同。

### 原型6

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr extents(span<OtherIndexType, Size> exts) noexcept;
```

`Size`==`rank()`且`Size`!=`rank_dynamic()`时采用本显式分支；元素条件与`array`形式相同。

### 原型7

```cpp
template<class OtherIndexType, size_t... OtherStaticExtents>
constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other) noexcept;
```

两侧秩相同，各静态维不得冲突。既不将来源动态维转为目标静态维，也不缩小`index_type`最大值时采用本非显式分支。

### 原型8

```cpp
template<class OtherIndexType, size_t... OtherStaticExtents>
explicit constexpr extents(const extents<OtherIndexType, OtherStaticExtents...>& other) noexcept;
```

两侧秩相同，各静态维不得冲突。目标含来源动态的静态维，或目标`index_type`最大值小于来源类型最大值时采用本显式分支。

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 逐维长度的类型包。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `dynvals` | 输入 | 按维度顺序提供的动态长度，或包含静态维的完整长度。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源`index_type`。 |
| `OtherStaticExtents` | 来源各维的静态长度或`dynamic_extent`标记。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源维度值；转换后的各值须可表示，且与目标静态维一致。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源`index_type`。 |
| `OtherStaticExtents` | 来源各维的静态长度或`dynamic_extent`标记。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源维度值；转换后的各值须可表示，且与目标静态维一致。 |

## 返回值说明

无返回值。

## 约束说明

- 所有运行时维长度须非负并能由`index_type`表示。
- 完整秩输入形式必须给出与静态维相同的值；动态维数量形式只提供动态位置。
- `array`/`span`的`Size`须等于`rank_dynamic()`或`rank()`；显式性按原型说明区分。
- `extents`只保存维度值，不借用输入`array`/`span`的存储，不分配或访问元素数据。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using dynamic_shape = asc::std::extents<int, asc::std::dynamic_extent, 3>;
    const asc::std::array<int, 1> dynamic_counts{{2}};
    const dynamic_shape from_array(dynamic_counts);
    const asc::std::extents<int, 2, 3> fixed(from_array);
    return from_array.extent(0) == 2 && from_array.extent(1) == 3
        && fixed.extent(0) == 2 && fixed.extent(1) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
