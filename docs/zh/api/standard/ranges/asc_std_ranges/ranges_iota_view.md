# asc::std::ranges::iota_view

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

`iota_view<Value, Bound>`按值保存起点和边界，以递增当前计数值生成序列；不借用用于构造起点的局部标量。默认边界为unreachable_sentinel_t，不自动生成有限长度。

## 声明

声明摘要保留公开默认实参；类型及成员操作仍须满足下述条件。

```cpp
namespace asc::std::ranges {
template<class Value, class Bound = unreachable_sentinel_t>
class iota_view;
}
```

## 约束说明

- Value必须支持所用的递增、比较和迭代运算；整数Value提供随机访问计数。
- 有界遍历须能安全到达结束条件，不得令计数运算溢出。
- 默认Bound不可达；对这种无界范围不能执行要求有限长度的完整遍历或size查询。

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
    asc::std::ranges::iota_view<int, int> view(3, 6);
    return *view.begin() == 3 && view.size() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
