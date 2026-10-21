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

所属类型：[`mdspan<Element, Extents, Layout, Accessor>`](mdspan.md)。以下按参与条件列出声明摘要，省略仅供SFINAE选择的实现参数；显式与非显式分支条件互斥。

### 原型1

```cpp
template<class Extents2 = Extents>
constexpr mdspan() noexcept(
    is_nothrow_default_constructible_v<data_handle_type>
    && is_nothrow_default_constructible_v<mapping_type>
    && is_nothrow_default_constructible_v<accessor_type>);
```

仅当`Extents2`至少含一个动态维，且数据句柄、对应映射及访问器均可默认构造时参与。

### 原型2

```cpp
constexpr mdspan(const mdspan& other) = default;
```

复制视图元数据；有效性与默认化特殊成员规则一致。

### 原型3

```cpp
constexpr mdspan(mdspan&& other) = default;
```

移动视图元数据；来源句柄状态由其类型的移动规则决定。

### 原型4

```cpp
template<class... OtherIndexTypes>
explicit constexpr mdspan(data_handle_type pointer, OtherIndexTypes... exts);
```

长度个数须等于`rank_dynamic()`或`rank()`；各值可转换且可不抛出异常地构造`index_type`，`mapping_type`可由`extents_type`构造，`accessor_type`可默认构造。

### 原型5

```cpp
template<class OtherIndexType, size_t Size>
constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts);
```

仅当`Size`==`rank_dynamic()`时选择本非显式分支。元素须可转换且可不抛出异常地构造`index_type`；映射须可由`extents_type`构造，访问器须可默认构造。

### 原型6

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& exts);
```

仅当`Size`==`rank()`且`Size`!=`rank_dynamic()`时选择本显式分支；其它构造条件与上一原型相同。

### 原型7

```cpp
template<class OtherIndexType, size_t Size>
constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts);
```

仅当`Size`==`rank_dynamic()`时选择本非显式分支；元素、映射和访问器条件与`array`形式相同。

### 原型8

```cpp
template<class OtherIndexType, size_t Size>
explicit constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> exts);
```

仅当`Size`==`rank()`且`Size`!=`rank_dynamic()`时选择本显式分支；元素、映射和访问器条件同上。

### 原型9

```cpp
template<class AccessorPolicy2 = Accessor, class Mapping2 = mapping_type>
constexpr mdspan(data_handle_type pointer, const extents_type& exts);
```

`AccessorPolicy2`须可默认构造，`Mapping2`须可由const `extents_type`&构造。

### 原型10

```cpp
template<class AccessorPolicy2 = Accessor>
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping);
```

`AccessorPolicy2`须可默认构造。

### 原型11

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping, const accessor_type& accessor);
```

按值保存所给句柄、映射和访问器；数据句柄须满足该访问器的访问条件。

### 原型12

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor>
constexpr mdspan(
    const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

目标`mapping`及`accessor`须可分别由来源`mapping`及`accessor`的const引用构造；两项都可隐式转换时选择本非显式分支。句柄须可由来源句柄构造，维度须可转换并满足目标静态长度。

### 原型13

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor>
explicit constexpr mdspan(
    const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

目标`mapping`及`accessor`须可分别由来源`mapping`及`accessor`的const引用构造；至少一项不能隐式转换时选择本显式分支。句柄须可由来源句柄构造，维度须可转换并满足目标静态长度。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents2` | 参与条件使用的维度类型，默认为`Extents`。 |

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源非拥有视图；构造复制或移动句柄、映射和访问器，不复制底层元素。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源非拥有视图；构造复制或移动句柄、映射和访问器，不复制底层元素。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 逐维长度实参类型包。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
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
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
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
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型7的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型8的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 来源长度元素的整数类型。 |
| `Size` | `array`或`span`的固定元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型9的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `AccessorPolicy2` | 访问器条件使用的类型，默认为`Accessor`。 |
| `Mapping2` | 映射条件使用的类型，默认为`mapping_type`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `exts` | 输入 | 来源维长度；可提供动态维数量或完整秩数量，各值须与静态维一致且可由`index_type`表示。 |

### 原型10的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `AccessorPolicy2` | 访问器条件使用的类型，默认为`Accessor`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `mapping` | 输入 | 保存的布局映射；决定逻辑索引如何换算为数据句柄偏移。 |

### 原型11的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 数据句柄；原存储须覆盖`mapping.required_span_size()`及访问器所需的有效访问范围，不获得所有权。 |
| `mapping` | 输入 | 保存的布局映射；决定逻辑索引如何换算为数据句柄偏移。 |
| `accessor` | 输入 | 保存的访问器；决定句柄类型、元素引用及地址空间或对齐要求。 |

### 原型12的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 来源元素类型。 |
| `OtherExtents` | 来源维度类型，秩及静态维须兼容。 |
| `OtherLayout` | 来源布局策略。 |
| `OtherAccessor` | 来源访问器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源非拥有视图；构造复制或移动句柄、映射和访问器，不复制底层元素。 |

### 原型13的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 来源元素类型。 |
| `OtherExtents` | 来源维度类型，秩及静态维须兼容。 |
| `OtherLayout` | 来源布局策略。 |
| `OtherAccessor` | 来源访问器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源非拥有视图；构造复制或移动句柄、映射和访问器，不复制底层元素。 |

## 返回值说明

无返回值。

## 约束说明

- 本页列出的构造形态从C++17起提供；元素访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 视图不拥有底层存储。存储、访问器及映射须共同保证每个有效索引都访问有效元素。
- 存储范围依`mapping.required_span_size()`及访问器要求确定，不能只按各维长度乘积估算；带步长间隙或填充的映射可能需要更多存储。
- 所有维长度须非负、可由`index_type`表示，完整长度形式须与静态extent一致。
- 数据句柄的地址空间及对齐要求由`Accessor`定义；本构造不执行额外的GM/UB转换。
- 默认构造的参与条件及异常规格见原型1；其它形式的模板参与条件分别见其原型说明。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    int storage[6] = {1, 2, 0, 0, 3, 4};
    using shape_type = asc::std::extents<asc::std::size_t, 2, 2>;
    const asc::std::array<asc::std::size_t, 2> strides{{4, 1}};
    const asc::std::layout_stride::mapping<shape_type> mapping(shape_type{}, strides);
    const asc::std::mdspan<int, shape_type, asc::std::layout_stride> view(storage, mapping);
    return view.size() == 4 && mapping.required_span_size() == 6 && view(1, 1) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
