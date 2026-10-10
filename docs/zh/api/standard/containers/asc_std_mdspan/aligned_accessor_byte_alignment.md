# asc::std::aligned_accessor::byte_alignment

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

`asc::std::aligned_accessor::byte_alignment` 给出访问器要求的数据起始地址对齐字节数。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
inline constexpr const size_t asc::std::aligned_accessor::byte_alignment
```

## 约束说明

- 固定当前版本的 C++ 标准库的完整layout_left/layout_right/layout_stride mapping及default_accessor/aligned_accessor家族：零rank与正rank、默认/extents/array/span/跨mapping或accessor构造、标准显式性与约束、索引映射、要求d_span_size/stride/extents、唯一/穷尽/步长观察、mapping比较、access/offset及byte_alignment
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/mdspan>

void example(const asc::std::aligned_accessor<int, 16>& object)
{
    (void)object.byte_alignment;
}
```
