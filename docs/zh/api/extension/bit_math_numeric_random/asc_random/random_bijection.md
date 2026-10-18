# asc::random_bijection

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

`asc::random_bijection`在有限索引域上构造由随机种子确定的一一映射。

## 声明

```cpp
namespace asc {
// 声明摘要：默认模板实参在下文说明。
template<class Index, class Bijection> class random_bijection;
} // namespace asc
```

`Index`默认使用64位无符号整数类型。`Bijection`默认使用库提供的置换实现，调用方可直接构造`asc::random_bijection<>`而无需命名默认实现类型。自定义`Bijection`须支持以范围大小和随机数生成器构造，并以`Index`值调用；在其置换域中反复调用必须能够返回到`[0, size)`。

## 约束说明

- 随机数引擎仅支持页面声明的无符号整数状态、种子和计数器形式。
- 不提供SeedSequence、流式输入输出或共享全局状态。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/random>

bool example()
{
    asc::pcg64 generator(7);
    asc::random_bijection<unsigned long long> permutation(4, generator);
    bool seen[4] = {};
    for (unsigned long long i = 0; i < 4; ++i) {
        const auto value = permutation(i);
        if (value >= 4 || seen[value]) return false;
        seen[value] = true;
    }
    return seen[0] && seen[1] && seen[2] && seen[3];
}
```

## 关联API

- [本头文件的接口列表](asc_random.md)
