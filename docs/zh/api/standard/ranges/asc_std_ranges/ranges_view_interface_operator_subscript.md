# asc::std::ranges::view_interface::`operator[]`

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::view_interface::operator[]`在调用方保证索引有效时访问指定元素。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`asc::std::ranges::view_interface`](ranges_view_interface.md)。

### 原型1

```cpp
// asc::std::ranges::view_interface 类内的声明节选；模板形参和其他成员由所属类提供。
template<class RARange> constexpr decltype(auto) operator[](range_difference_t<RARange> index);
```

### 原型2

```cpp
// asc::std::ranges::view_interface 类内的声明节选；模板形参和其他成员由所属类提供。
template<class RARange> constexpr decltype(auto) operator[](range_difference_t<RARange> index) const;
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RARange` | 派生自view_interface的随机访问范围/视图类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 元素下标，从0起；调用方须保证0 <= index < 范围长度，接口不检查越界。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RARange` | 派生自view_interface的随机访问范围/视图类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `index` | 输入 | 元素下标，从0起；调用方须保证0 <= index < 范围长度，接口不检查越界。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `decltype(auto)` | 返回指定索引处的元素引用或代理值；索引必须有效。 |
| 原型2 | `decltype(auto)` | 返回指定索引处的元素引用或代理值；索引必须有效。 |

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。

## 调用示例

以下Host片段在底层存储存活期内完成访问，返回元素值的副本，不把局部数组元素引用传出函数。

```cpp
#include <asc/std/ranges>

int read_first_element()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::ranges::ref_view<int[4]> view(values);
    // 前置条件：index < size()；operator[] 不执行边界检查
    return view[0];
}
```

## 关联API

- [`asc::std::ranges::view_interface`](ranges_view_interface.md)
- [本头文件的接口列表](asc_std_ranges.md)
