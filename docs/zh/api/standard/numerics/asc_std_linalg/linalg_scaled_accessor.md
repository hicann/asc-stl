# asc::std::linalg::scaled_accessor

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

`asc::std::linalg::scaled_accessor`定义按值读取计算结果的访问策略；不通过返回值写回底层元素。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 声明

```cpp
namespace asc::std::linalg {
template<class ScalingFactor, class NestedAccessor> class scaled_accessor;
} // namespace asc::std::linalg
```

## 约束说明

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>
#include <asc/std/type_traits>

using Accessor = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;

bool example()
{
    float values[] = {3.0f};
    Accessor accessor(2.0f, asc::std::default_accessor<float>{});
    auto value = accessor.access(values, 0);
    return value == 6.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
