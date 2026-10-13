# asc::pcg64_engine

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

`asc::pcg64_engine`实现可设种子、可跳过输出的确定性64位PCG伪随机数引擎。

## 声明

```cpp
namespace asc {
template<asc::std::uint64_t AHigh, asc::std::uint64_t ALow, asc::std::uint64_t CHigh, asc::std::uint64_t CLow> class pcg64_engine;
} // namespace asc
```

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 first(7);
    asc::pcg64 second(7);
    return first() == second() && first() == second();
}
```

## 关联API

- [本头文件的接口列表](asc_random.md)
