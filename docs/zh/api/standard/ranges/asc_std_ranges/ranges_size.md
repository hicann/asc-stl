# asc::std::ranges::size

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

`asc::std::ranges::size`取得范围的元素数量。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该公开名称为常量可调用对象，不是自由函数；其实现类不属于公开契约。以下仅查询对象类型，object_type是示例名称。调用形式见参数说明及示例。

```cpp
using object_type = decltype(asc::std::ranges::size);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |

## 返回值说明

- 已知界限的数组返回`size_t`类型的数组长度。
- 成员`size()`或ADL `size`路径返回该调用结果去除引用和顶层cv后的整数类型，可能是有符号类型。
- 起止迭代器差值回退路径返回其无符号数量类型。不能统一假定所有返回值均为无符号数。

## 约束说明

- 依次尝试已知界限数组、可用的成员size、ADL size、最后是满足forward_iterator与sized_sentinel_for的差值。
- disable_sized_range会屏蔽成员与ADL分支，不能简单理解为屏蔽所有大小查询。
- 底层对象须在调用期间有效；结果是数量值，不延长元素寿命。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

struct example_range { int size() const noexcept { return 3; } };

bool example()
{
    example_range values;
    const auto count = asc::std::ranges::size(values);
    static_assert(asc::std::is_same_v<asc::std::remove_cv_t<decltype(count)>, int>);
    return count == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
