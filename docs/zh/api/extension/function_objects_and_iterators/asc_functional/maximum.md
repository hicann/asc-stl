# asc::maximum

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

头文件：`<asc/functional>`。比较两个输入并按值返回较大者。

## 声明

```cpp
namespace asc {
template<class T = void> struct maximum;
}  // namespace asc
```

## 约束说明

默认T为void，提供透明异型调用；指定类型版本返回T。两个版本均不返回形参引用。

C++17和C++20均支持。Host、SIMT、SIMD标量调用须满足当前调用域的比较、转换、构造和析构要求；Device调用遵守无异常执行约定。

## 调用示例

```cpp
#include <asc/functional>

bool example()
{
    return asc::maximum<>{}(3, 7L) == 7;
}
```

## 关联API

- [本头文件的接口列表与运算支持表](asc_functional.md)
