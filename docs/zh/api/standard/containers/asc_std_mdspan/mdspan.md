# asc::std::mdspan

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

`asc::std::mdspan`以非拥有方式关联多维数据句柄、维度、布局和访问器。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
namespace asc::std {
template<class Element, class Extents, class Layout, class Accessor> class mdspan;
} // namespace asc::std
```

## 约束说明

- C++17起提供一维`operator[]`及以array/span保存索引的访问形式；多参数`operator[]`要求编译器支持C++23多维下标语法。
- C++17和C++20可使用`operator()`扩展按逐维下标访问；该形式的下标数量须等于维数。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    asc::std::mdspan<int, asc::std::extents<int, 2, 3>> view(values);
    view(1, 2) = 9;
    return view.extent(0) == 2 && view.extent(1) == 3 && values[5] == 9;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
