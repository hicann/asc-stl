# asc::std::shuffle

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

`asc::std::shuffle` 使用调用方提供的随机引擎重排范围；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

```cpp
template<class RandomAccessIterator, class UniformRandomNumberGenerator> void asc::std::shuffle(RandomAccessIterator first, RandomAccessIterator last, UniformRandomNumberGenerator&& g);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RandomAccessIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `UniformRandomNumberGenerator` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `g` | 输入/输出 | 提供“使用调用方提供的随机引擎重排范围”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

无返回值。

## 约束说明

- 随机数引擎由调用方提供，并且必须满足 URBG 要求
- 结果类型为 float

## 调用示例

以下 Host 片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>


#include <asc/std/random>
void example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::minstd_rand random_engine(9);
    asc::std::shuffle(values, values + 8, random_engine);
}
```
