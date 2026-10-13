# asc::std::span

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

头文件路径为：`<asc/std/span>`。

`asc::std::span`以非拥有方式观察一段连续元素。

标准语义参考：[cppreference `span`](https://en.cppreference.com/w/cpp/header/span)。

## 声明

```cpp
namespace asc::std {
template<typename T, size_t Extent> class span;
} // namespace asc::std
```

## 约束说明

- 支持固定或动态extent，以及指针、数组和兼容的连续范围。
- AI Core SIMD编程 中仅当元素指针或范围可表示为标准普通指针时才可使用，不提供非标准GM/UB指针重载。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/span>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::span<int> view(values, 4);
    view[1] = 8;
    auto tail = view.subspan(2, 2);
    return values[1] == 8 && tail.size() == 2 && tail[0] == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_span.md)
