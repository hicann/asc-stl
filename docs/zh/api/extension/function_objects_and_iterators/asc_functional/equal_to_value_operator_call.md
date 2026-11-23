# asc::equal_to_value::operator()

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

头文件：`<asc/functional>`。按输入在左、保存值在右的方向比较，返回bool。

## 声明

```cpp
// Inside equal_to_value<T>; declaration constraints are omitted.
template<class U>
constexpr bool operator()(const U& input) const
    noexcept(noexcept(static_cast<bool>(input == value_)));
```

## 约束说明

支持异型const左值比较，使用static_cast<bool>(input == value_)，不消耗保存值。比较或显式bool转换无效时排除调用；noexcept覆盖比较、转换及相关临时析构。C++20比较重写候选按语言规则处理。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>

bool example()
{
    const asc::equal_to_value<int> equal(7);
    return equal(7L) && !equal(8L);
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
