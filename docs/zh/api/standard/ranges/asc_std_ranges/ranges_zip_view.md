# asc::std::ranges::zip_view

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

`zip_view<FirstView, SecondView>`同步遍历恰好两个底层视图，以两个元素引用组成的tuple表示当前元素；长度取两者较短者。

## 声明

```cpp
namespace asc::std::ranges {
template<class FirstView, class SecondView>
class zip_view;
}
```

## 约束说明

- 当前只支持恰好两个随机访问且有大小的范围；不支持任意个视图包。
- 解引用所得tuple保留底层引用，可向可写元素写回；它不复制或取得底层元素所有权。
- const迭代要求两侧可const遍历，且各自const迭代器类型与非const形式相同。
- 实际借用的底层存储须覆盖所有迭代访问。

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
    asc::std::ranges::zip_view<Base, Base> view(base, base);
    auto item = *view.begin();
    return asc::std::get<0>(item) == 1 && asc::std::get<1>(item) == 1 && view.size() == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
