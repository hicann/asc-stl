# asc::std::ranges::views::zip

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

`asc::std::ranges::views::zip`将恰好两个可确定大小的随机访问范围按位置配对，所得视图在较短的输入范围结束时结束。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
// asc::std::ranges::views 类内的声明节选；模板形参和其他成员由所属类提供。
zip(first_range, second_range);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first_range` | 输入 | 第一个待组合的输入范围。 |
| `second_range` | 输入 | 第二个待组合的输入范围。 |

## 返回值说明

返回同步遍历两个输入范围的视图，长度由较短的输入范围决定。

| 调用形式 | 返回类型 |
| --- | --- |
| 两个范围 | `zip_view<decltype(views::all(first_range)), decltype(views::all(second_range))>` |

## 约束说明

- 七个列出名称。
- 有限repeat、两路random-access+sized zip引用写回、单次range|closure。
- Host、AI Core SIMD编程 和AI Core SIMT编程。
- 本期只支持两个具备随机访问能力且可确定大小的范围。
- 所得视图的引用不得超过任一输入范围的有效期。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto view = asc::std::ranges::views::zip(values, values);
    return asc::std::get<0>(*view.begin()) == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
