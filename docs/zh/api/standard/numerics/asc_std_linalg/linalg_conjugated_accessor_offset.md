# asc::std::linalg::conjugated_accessor::offset

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

头文件路径为：`<asc/std/linalg>`。

`asc::std::linalg::conjugated_accessor::offset` 按映射结果移动底层数据句柄。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

```cpp
[[nodiscard]] constexpr typename offset_policy::data_handle_type asc::std::linalg::conjugated_accessor::offset(data_handle_type pointer, size_t index) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 待移动的底层数据句柄。 |
| `index` | 输入 | 句柄向前移动的元素个数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `typename offset_policy::data_handle_type` | 返回给定多维索引映射到的底层存储偏移。 |

## 约束说明

- 固定当前版本的 C++ 标准库公共入口的完整7实体合同：scaled/scaled_accessor、conjugated/conjugated_accessor、transposed/layout_transpose、conjugate_transposed
- 包括access/offset/nested accessor/factor、转换构造、算术类型共轭不变、ADL可共轭类型、双重共轭/转置消去、rank-2静态/动态extents交换、layout_left/right/stride与通用layout_transpose mapping全部观察/比较
- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段使用具体范围或访问器演示调用；底层存储在调用期间须保持有效。

```cpp
#include <asc/std/linalg>

decltype(auto) example()
{
    asc::std::complex<float> values[2]{};
    using accessor_type = asc::std::linalg::conjugated_accessor<asc::std::default_accessor<asc::std::complex<float>>>;
    accessor_type accessor{};
    return accessor.offset(values, 0);
}
```
