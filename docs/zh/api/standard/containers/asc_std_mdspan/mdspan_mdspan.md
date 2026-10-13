# asc::std::mdspan::mdspan

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

`asc::std::mdspan::mdspan`按本页所列构造形态初始化`mdspan`对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型1

```cpp
constexpr mdspan() noexcept;
```

### 原型2

```cpp
constexpr mdspan(const mdspan<Element, Extents, Layout, Accessor>& other);
```

### 原型3

```cpp
constexpr mdspan(data_handle_type pointer, const Extents& extents);
```

### 原型4

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping);
```

### 原型5

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping, const Accessor& accessor);
```

### 原型6

```cpp
constexpr mdspan(mdspan<Element, Extents, Layout, Accessor>&& other);
```

### 原型7

```cpp
template<class ...OtherIndexTypes> constexpr mdspan(data_handle_type pointer, OtherIndexTypes... args);
```

### 原型8

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor> constexpr mdspan(const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

### 原型9

```cpp
template<class OtherIndexType, size_t Size> constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& count);
```

### 原型10

```cpp
template<class OtherIndexType, size_t Size> constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> count);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制的另一mdspan视图；本对象拷贝其数据句柄、布局映射与访问器，与它共享同一底层存储且不拥有该存储。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `extents` | 输入 | 维度描述对象（extents）；其秩与各维长度须与pointer指向的存储匹配。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `mapping` | 输入 | 布局映射对象；定义各维索引到数据句柄偏移的换算规则，本对象保存其副本。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `mapping` | 输入 | 布局映射对象；定义各维索引到数据句柄偏移的换算规则，本对象保存其副本。 |
| `accessor` | 输入 | 访问器对象；定义元素访问方式与对齐要求，本对象保存其副本。 |

### 原型6的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 被移动构造的另一mdspan视图；其数据句柄、布局映射与访问器转移给本对象，移动后它处于有效但未指定的状态。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 依次给出各维长度的整数类型包；各类型须可转换为index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `args` | 输入 | 按维度顺序给出的各维长度实参包；个数须等于秩且各值非负。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 源mdspan的元素类型，须可转换为本视图的元素类型。 |
| `OtherExtents` | 源mdspan的维度描述类型，须与本视图的秩和静态维长度兼容。 |
| `OtherLayout` | 源mdspan的布局策略类型，须与本视图的布局兼容。 |
| `OtherAccessor` | 源mdspan的访问器类型，其元素类型须可转换为本视图的元素类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 用于跨类型构造的另一mdspan视图；其元素类型可转换为本视图的元素类型，维度与访问策略兼容。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | count中各维长度的整数类型，须可转换为index_type。 |
| `Size` | count的元素个数，编译期常量，须等于本视图的秩。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `count` | 输入 | 按维度顺序存放各维长度的array；元素个数须等于秩且各值非负。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | count中各维长度的整数类型，须可转换为index_type。 |
| `Size` | count的元素个数，编译期常量，须等于本视图的秩。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被视图首元素的数据句柄；须指向可覆盖各维长度乘积个元素的连续存储。 |
| `count` | 输入 | 按维度顺序存放各维长度的span；元素个数须等于秩且各值非负。 |

## 返回值说明

无返回值。

## 约束说明

- C++20开放rank-one `operator[]`，C++2b条件开放标准多索引operator[]。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    return view(1, 2) == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
