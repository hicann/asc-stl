# asc::std::generate_canonical

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

头文件路径为：`<asc/std/random>`。

`asc::std::generate_canonical`使用调用方随机引擎生成指定精度的浮点随机值。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

```cpp
namespace asc::std {
template<class RealType, size_t Bits, class URng> [[nodiscard]] constexpr RealType generate_canonical(URng& generator) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RealType` | 随机引擎或分布产生的数值类型；须符合当前引擎或分布的整数／浮点要求。 |
| `Bits` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |
| `URng` | 均匀随机位生成器类型，提供无参调用、min和max。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `generator` | 输入/输出 | 提供随机数的生成器；调用时其状态可能推进。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `RealType` | 返回推进随机引擎后产生的下一个随机值。 |

## 约束说明

- 随机数引擎由调用方提供，并且必须满足URBG要求。
- 结果类型为float。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/random>

decltype(auto) example()
{
    asc::std::minstd_rand engine;
    return asc::std::generate_canonical<float, 10>(engine);
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
