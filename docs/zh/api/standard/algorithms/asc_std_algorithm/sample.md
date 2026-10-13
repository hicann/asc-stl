# asc::std::sample

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::sample`从输入范围随机选取指定数量的元素；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

```cpp
namespace asc::std {
template<class PopulationIterator, class SampleIterator, class Distance, class UniformRandomNumberGenerator> SampleIterator sample(PopulationIterator first, PopulationIterator last, SampleIterator output_iter, Distance n, UniformRandomNumberGenerator&& g);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `PopulationIterator` | 遍历总体（输入）范围的迭代器类型；须满足输入迭代器以上的遍历能力。 |
| `SampleIterator` | 写入采样结果的输出迭代器类型；总体为前向迭代器时结果保持原有相对顺序。 |
| `Distance` | 表示采样个数与范围距离的整数类型。 |
| `UniformRandomNumberGenerator` | 均匀随机数生成器类型；调用形式为g()，返回值可转换为unsigned整数。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 总体（输入）范围的起始迭代器或指针。 |
| `last` | 输入 | 总体（输入）范围的结束位置，不包含该位置。 |
| `output_iter` | 输出 | 写入采样结果的输出迭代器；目标范围容量须足以容纳min(n, 输入范围长度)个元素。 |
| `n` | 输入 | 期望采样的元素个数；实际写入个数不超过min(n, 输入范围长度)。 |
| `g` | 输入/输出 | 均匀随机数生成器对象，按调用形式g()产生随机数；采样期间其状态被推进。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `SampleIterator` | 返回输出范围中最后一个写入元素之后的位置。 |

## 约束说明

- 随机数引擎由调用方提供，并且必须满足URBG要求。
- 结果类型为float。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>


#include <asc/std/random>
decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    asc::std::minstd_rand random_engine(9);
    return asc::std::sample(values, values + 8, output, 4, random_engine);
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
