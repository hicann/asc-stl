# asc::always_false::operator()

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

头文件：`<asc/functional>`。接受零个或多个实参并返回false。

## 声明

```cpp
template<class... Args>
constexpr bool operator()(Args&&...) const noexcept;
```

## 约束说明

无状态，调用无条件noexcept，函数体不读取、复制或保存参数。调用方实参表达式仍会求值，可能产生副作用或抛异常。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>

bool example()
{
    int evaluations = 0;
    const bool result = asc::always_false{}(++evaluations);
    return !result && evaluations == 1;
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
