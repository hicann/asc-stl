# asc::std::default_accessor::access

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

`asc::std::default_accessor::access`通过访问器取得指定索引处的元素引用。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`asc::std::default_accessor`](default_accessor.md)。

```cpp
// asc::std::default_accessor 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr reference access(data_handle_type pointer, size_t index) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 指向被访问元素存储的数据句柄（元素指针）；须可访问自其起第index个元素。 |
| `index` | 输入 | 相对pointer的元素下标，从0起；返回 *(pointer + index)处的元素引用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reference` | 返回给定多维索引对应的元素引用或访问结果。 |

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host片段在底层存储存活期内完成访问，返回元素值的副本，不把局部数组元素引用传出函数。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    int data[4] = {1, 2, 3, 4};
    asc::std::default_accessor<int> accessor;
    accessor.access(data, 1) = 9;
    return data[1] == 9 && accessor.access(data, 0) == 1;
}
```

## 关联API

- [`asc::std::default_accessor`](default_accessor.md)
- [本头文件的接口列表](asc_std_mdspan.md)
