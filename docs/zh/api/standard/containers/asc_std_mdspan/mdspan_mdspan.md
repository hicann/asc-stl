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

`asc::std::mdspan::mdspan` 按本页所列构造形态初始化 `mdspan` 对象。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
constexpr mdspan() noexcept;
```

### 原型 2

```cpp
constexpr mdspan(const mdspan<Element, Extents, Layout, Accessor>& other);
```

### 原型 3

```cpp
constexpr mdspan(data_handle_type pointer, const Extents& extents);
```

### 原型 4

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping);
```

### 原型 5

```cpp
constexpr mdspan(data_handle_type pointer, const mapping_type& mapping, const Accessor& accessor);
```

### 原型 6

```cpp
constexpr mdspan(mdspan<Element, Extents, Layout, Accessor>&& other);
```

### 原型 7

```cpp
template<class ...OtherIndexTypes> constexpr mdspan(data_handle_type pointer, OtherIndexTypes... args);
```

### 原型 8

```cpp
template<class OtherElement, class OtherExtents, class OtherLayout, class OtherAccessor> constexpr mdspan(const mdspan<OtherElement, OtherExtents, OtherLayout, OtherAccessor>& other);
```

### 原型 9

```cpp
template<class OtherIndexType, size_t Size> constexpr mdspan(data_handle_type pointer, const array<OtherIndexType, Size>& count);
```

### 原型 10

```cpp
template<class OtherIndexType, size_t Size> constexpr mdspan(data_handle_type pointer, span<OtherIndexType, Size> count);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `extents` | 输入 | 各维的有效长度；维度数量和取值范围须满足本页约束。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `mapping` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `mapping` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `accessor` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 6 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 7 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexTypes` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

### 原型 8 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherElement` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `OtherExtents` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `OtherLayout` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `OtherAccessor` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 9 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `count` | 输入 | 参与操作的元素数量。 |

### 原型 10 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherIndexType` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“按本页所列构造形态初始化 `mdspan` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `count` | 输入 | 参与操作的元素数量。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整标准mdspan view家族：全部成员类型与rank/static_extent观察，默认/拷贝/移动、data_handle+维度包/array/span/extents/mapping/mapping+accessor及跨mdspan构造，赋值与deduction guides，array/span下标、size/empty/swap、data_handle/mapping/accessor/extents/extent及映射属性观察
- C++20开放rank-one operator[]，C++2b条件开放标准多索引operator[]
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下 Host 片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void example()
{
    asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>> view{};
    (void)view.rank();
}
```
