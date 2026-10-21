# asc::std::ranges::repeat_view

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

`repeat_view<T, Bound>`保存一个T值，迭代器的每次解引用返回该值的const T&，次数由Bound决定。默认Bound为ptrdiff_t，默认次数为0。

## 声明

声明摘要保留公开默认实参；类型及成员操作仍须满足下述条件。

```cpp
namespace asc::std::ranges {
template<class T, class Bound = ptrdiff_t>
class repeat_view;
}
```

## 约束说明

- T须为无cv限定的对象类型且可移动构造；Bound须满足semiregular，并为有可用差值类型的整数类型或unreachable_sentinel_t。
- 有界次数须非负；显式值构造必须提供边界实参。
- views::repeat只提供接收值与边界的两个实参形式；单实参无界工厂未提供。
- 每次解引用借用视图内部保存的同一个值；视图须覆盖引用与迭代器使用期。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    asc::std::ranges::repeat_view<int, int> view(7, 3);
    return *view.begin() == 7 && view.size() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
