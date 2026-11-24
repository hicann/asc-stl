# asc::sincos

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

头文件路径为：`<asc/cmath>`。

输入角度单位为弧度，一次调用将正弦写入 sin_out、余弦写入 cos_out，返回 void。

## 函数原型

```cpp
namespace asc {
void sincos(float value, float* sin_out, float* cos_out) noexcept;
void sincos(double value, double* sin_out, double* cos_out) noexcept;
void sincos(long double value, long double* sin_out, long double* cos_out) noexcept;
}
```

## 参数说明

`value`为输入弧度；两个输出指针分别指向正弦和余弦对象。

## 返回值说明

`void` — 输入角度单位为弧度，一次调用将正弦写入 sin_out、余弦写入 cos_out，返回 void。

## 约束说明

两个指针须非空、对齐并指向生命周期内可写且当前执行位置可访问的同类型对象，完整存储区间不重叠。SIMT可写可访问的GM、UB或线程栈，调用方负责并发访问和同步。

正负零的正弦保留符号，余弦为1；NaN或正负无穷的两结果均为NaN，不规定载荷。全部有限角度（含大有限值）的精度沿用同类型、同环境和数学选项下的sin/cos，不规定统一ULP上界或逐位一致。特殊值契约要求保留NaN/无穷/有符号零语义的配置；快速数学放宽行为按工具链文档。无统一errno/浮点异常标志，不是constexpr。一次调用不保证单条硬件指令或性能提升。

没有整数/枚举模板；普通隐式转换按输出指针类型选择重载，整数可能舍入，bool对应0或1弧度，scoped enum须显式转换。低精度格式先显式转换到所需浮点类型。

float: Host与950 SIMT，要求CANN的simt_api/math_functions.h提供sincosf；double仅Host，long double仅在标准层/Host配置提供该重载时开放。普通SIMD控制代码不提供标量sincos。

## 调用示例

```cpp
#include <asc/cmath>

bool verify_example()
{
    float sine{}, cosine{};
    asc::sincos(-0.0F, &sine, &cosine);
    return sine == 0.0F && asc::std::signbit(sine) && cosine == 1.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_cmath.md)
