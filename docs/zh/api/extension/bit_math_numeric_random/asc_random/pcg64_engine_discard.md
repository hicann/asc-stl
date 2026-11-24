# asc::pcg64::discard

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

头文件路径为：`<asc/random>`。

以对数时间推进原始序列，等价于取数 count 次并丢弃结果。

## 声明

成员属于 [`asc::pcg64`](pcg64.md)，以下为类内声明。

```cpp
constexpr void discard(unsigned long long count) noexcept;
```

## 约束说明

支持 C++17/C++20 的 Host、Ascend 950 SIMT 和 SIMD 核普通整数标量代码；所有操作 constexpr、noexcept。

完整算法、播种、比较和推进规则见 [pcg64](pcg64.md)。

## 调用示例

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 engine(42);
    engine.discard(1ULL << 63);
    return engine() == 17290396888909922309ULL;
}
```

## 关联API

- [本头文件的接口列表](asc_random.md)
