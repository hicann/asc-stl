# asc::absorbing_element

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

头文件：`<asc/functional>`。返回已登记的双侧吸收元，类型为T。

## 声明

```cpp
namespace asc {
template<class Operator, class T,
    asc::std::enable_if_t<has_absorbing_element_v<Operator, T>, int> = 0>
constexpr T absorbing_element() noexcept;
}  // namespace asc
```

## 约束说明

has_absorbing_element_v为true时才参与重载，false时表达式检测亦不可调用。单位元满足F(e,x)=F(x,e)=x，吸收元满足F(z,x)=F(x,z)=z，其中F在每个节点转换回T。仅保证数值结果，不改变实参求值及副作用规则。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>
#include <asc/std/limits>

bool example()
{
    return asc::absorbing_element<asc::maximum<int>, int>() ==
        (asc::std::numeric_limits<int>::max)();
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
