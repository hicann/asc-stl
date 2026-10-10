# asc::std::mdspan::operator=

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

`asc::std::mdspan::operator=` 按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

### 原型 1

```cpp
constexpr mdspan<Element, Extents, Layout, Accessor>& asc::std::mdspan::operator=(const mdspan<Element, Extents, Layout, Accessor>& other);
```

### 原型 2

```cpp
constexpr mdspan<Element, Extents, Layout, Accessor>& asc::std::mdspan::operator=(mdspan<Element, Extents, Layout, Accessor>&& other);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `mdspan<Element, Extents, Layout, Accessor> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |
| 原型 2 | `mdspan<Element, Extents, Layout, Accessor> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整标准mdspan view家族：全部成员类型与rank/static_extent观察，默认/拷贝/移动、data_handle+维度包/array/span/extents/mapping/mapping+accessor及跨mdspan构造，赋值与deduction guides，array/span下标、size/empty/swap、data_handle/mapping/accessor/extents/extent及映射属性观察
- C++20开放rank-one operator[]，C++2b条件开放标准多索引operator[]
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下 Host 片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void example(asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>& target, const asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>& source)
{
    target = source;
}
```
