# asc::std::ranges::views::all

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

`asc::std::ranges::views::all`把输入范围转为适当的非拥有或拥有式视图。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该公开名称为常量可调用对象，不是自由函数；其实现类不属于公开契约。以下仅查询对象类型，object_type是示例名称。调用形式见参数说明及示例。

```cpp
using object_type = decltype(asc::std::ranges::views::all);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |

## 返回值说明

| 输入条件（按顺序选择） | 返回结果 |
| --- | --- |
| 去除cv/ref后已是view，且能由输入构造 | 按值复制或移动该view类型；借用性由该view自身决定。 |
| 其它可由ref_view关联的输入 | ref_view，通常为外部范围的左值；不取得元素所有权。 |
| 其它满足viewable_range并可由owning_view保存的输入 | owning_view，保存被移动的范围对象；该对象是否拥有元素仍取决于底层范围类型。 |

## 约束说明

- 输入须满足viewable_range，选择按上述优先级进行，不能仅按左值/右值判断所有权。
- 右值ref_view仍借用原范围；复制一个非拥有view不复制底层元素，也不延长元素寿命。
- 所有借用存储须覆盖视图和迭代器的实际访问期。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>
#include <asc/std/utility>

bool example()
{
    int values[3] = {1, 2, 3};
    auto original = asc::std::ranges::views::all(values);
    auto copied = asc::std::ranges::views::all(original);
    auto moved = asc::std::ranges::views::all(asc::std::move(original));
    static_assert(asc::std::is_same_v<decltype(copied), decltype(moved)>);
    return copied.data() == values && moved.data() == values && moved.size() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
