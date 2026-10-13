# asc::std::linalg::conjugated_accessor::nested_accessor

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

`asc::std::linalg::conjugated_accessor::nested_accessor`返回组合访问器内部保存的访问器。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

所属类型：[`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)。

```cpp
// asc::std::linalg::conjugated_accessor 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr const NestedAccessor& nested_accessor() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `const NestedAccessor &` | 返回组合访问器内部保存的访问器。 |

## 约束说明

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host片段使用具体范围或访问器演示调用；底层存储在调用期间须保持有效。

```cpp
#include <asc/std/linalg>

decltype(auto) example()
{
    using accessor_type = asc::std::linalg::conjugated_accessor<asc::std::default_accessor<asc::std::complex<float>>>;
    accessor_type accessor{};
    return accessor.nested_accessor();
}
```

## 关联API

- [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)
- [本头文件的接口列表](asc_std_linalg.md)
