# asc::std::mdspan::`operator()`

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

`asc::std::mdspan::operator()`按多维下标访问元素，下标个数须等于维数且均可转换为索引类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

```cpp
// asc::std::mdspan<Element, Extents, Layout, Accessor> 类内声明摘要。
// 省略内部 SFINAE：Indices... 均须可转换为 index_type。
template<class... Indices>
[[nodiscard]] constexpr reference operator()(Indices... indices) const;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Indices` | 每一维下标的实参类型，须能转换为index_type。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `indices` | 输入 | 逐维下标，个数必须为rank()，第r维满足0 <= index < extent(r)。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reference` | 通过mapping计算偏移并交由accessor访问所得的结果；具体引用或代理值类型由Accessor::reference决定。 |

## 约束说明

- 下标个数等于维数且每个下标可显式转换为索引类型。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::mdspan<int, asc::std::extents<int, 2, 2>> view(values);
    view(1, 0) = 7;
    return values[2] == 7 && view(0, 1) == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
