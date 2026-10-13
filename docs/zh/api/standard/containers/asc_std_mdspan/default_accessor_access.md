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

`asc::std::default_accessor::access` 通过访问器取得指定索引处的元素引用。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

```cpp
constexpr reference asc::std::default_accessor::access(data_handle_type pointer, size_t index) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“通过访问器取得指定索引处的元素引用”所需的输入对象；类型须满足所选原型约束。 |
| `index` | 输入 | 指定“通过访问器取得指定索引处的元素引用”使用的标量值；取值须满足声明和约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reference` | 返回给定多维索引对应的元素引用或访问结果。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整layout_left/layout_right/layout_stride mapping及default_accessor/aligned_accessor家族：零rank与正rank、默认/extents/array/span/跨mapping或accessor构造、标准显式性与约束、索引映射、要求d_span_size/stride/extents、唯一/穷尽/步长观察、mapping比较、access/offset及byte_alignment
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下 Host 片段在底层存储存活期内完成访问，返回元素值的副本，不把局部数组元素引用传出函数。

```cpp
#include <asc/std/mdspan>

int read_first_element()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    asc::std::default_accessor<int> accessor{};
    // 前置条件：索引 0 < 4；access 不执行边界检查
    return accessor.access(values, 0);
}
```
