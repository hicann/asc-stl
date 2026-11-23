# asc::has_identity_element_v

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

头文件：`<asc/functional>`。该运算和值类型组合是否有登记的双侧单位元。

## 声明

```cpp
namespace asc {
template<class Operator, class T>
inline constexpr bool has_identity_element_v = /* library registration */;
}  // namespace asc
```

## 约束说明

Operator和T使用精确无cv/ref类型。对const T左值调用运算，每个二元节点将结果转换回T；以T全值域上的内建数值==为等价关系。结合律与交换律分别登记。false表示未提供保证，表外组合均为false。完整支持表见本头总览。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>

bool example()
{
    static_assert(asc::has_identity_element_v<asc::maximum<unsigned>, unsigned>);
    static_assert(!asc::has_identity_element_v<asc::maximum<float>, float>);
    return true;
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
