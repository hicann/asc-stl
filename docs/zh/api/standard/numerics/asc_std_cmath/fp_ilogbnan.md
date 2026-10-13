# FP_ILOGBNAN

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

头文件路径为：`<asc/std/cmath>`。

`FP_ILOGBNAN`是`asc::std::ilogb`接收NaN时返回的标准失败值。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 声明

宏的具体整数值由数学实现定义。使用宏名判断对应的NaN指数结果，不依赖固定数值。

```cpp
#include <asc/std/cmath>

constexpr auto nan_exponent = FP_ILOGBNAN;
```

## 约束说明

- 包含`<asc/std/cmath>`后始终定义。
- 宏值为INT_MIN或INT_MAX，由当前数学实现决定。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>
#include <asc/std/climits>

#ifndef FP_ILOGBNAN
#error "FP_ILOGBNAN is required by this public Header"
#endif
static_assert(FP_ILOGBNAN == INT_MIN || FP_ILOGBNAN == INT_MAX);
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
