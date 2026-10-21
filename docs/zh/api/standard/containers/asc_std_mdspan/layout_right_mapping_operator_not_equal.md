# asc::std::layout_right::mapping::`operator!=`

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

`asc::std::layout_right::mapping::operator!=`为相等比较的取反：两个映射在维数相同且逐维extent与偏移相等时相等。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型为`layout_right`::`mapping`<`Extents`>。以下为隐藏友元的声明摘要，省略仅用于参与选择的实现参数；以运算符语法调用。

### 原型1

```cpp
template<class OtherExtents>
friend constexpr bool operator!=(const mapping& left, const mapping<OtherExtents>& right) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherExtents` | 另一映射的维度类型；秩须相同。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 左侧布局映射；比较其维度及适用的步长信息。 |
| `right` | 输入 | 右侧布局映射；不读取底层元素。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 两映射不等时返回`true`。 |

## 约束说明

- 两侧`mapping`的秩须相同。
- 上述显式不等函数仅在C++17提供；C++20由相等运算符重写不等调用。
- 比较维度及对应的布局信息，不访问或比较底层元素。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using shape_type = asc::std::extents<asc::std::size_t, 2, 3>;
    using mapping_type = asc::std::layout_right::mapping<shape_type>;
    const mapping_type first(shape_type{});
    const mapping_type second(shape_type{});
    return !(first != second);
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
