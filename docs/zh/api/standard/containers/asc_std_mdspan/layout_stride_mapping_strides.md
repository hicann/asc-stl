# asc::std::layout_stride::mapping::strides

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

`asc::std::layout_stride::mapping::strides`返回各维步长数组。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

```cpp
asc::std::array<typename asc::std::layout_stride::mapping<Extents>::index_type, Extents::rank()> asc::std::layout_stride::mapping<Extents>::strides() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `按声明确定` | 按维度顺序保存各维步长的数组副本。 |

## 约束说明

- 步长数组与维数一致，恒不抛出。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    using shape = asc::std::extents<::std::size_t, 2, 3>;
    const asc::std::array<::std::size_t, 2> input{4, 1};
    asc::std::layout_stride::mapping<shape> mapping(shape{}, input);
    const auto strides = mapping.strides();
    return strides[0] == 4 && strides[1] == 1 && mapping(1, 2) == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
