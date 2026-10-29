# asc::std::uniform_int_distribution::`operator()`

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

`asc::std::uniform_int_distribution::operator()`按`uniform_int_distribution`的可用运算符规则处理当前对象及操作数。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::uniform_int_distribution`](uniform_int_distribution.md)。

### 原型1

```cpp
// asc::std::uniform_int_distribution 类内的声明节选；模板形参和其他成员由所属类提供。
template<class URng> constexpr result_type operator()(URng& generator) noexcept;
```

### 原型2

```cpp
// asc::std::uniform_int_distribution 类内的声明节选；模板形参和其他成员由所属类提供。
template<class URng> constexpr result_type operator()(URng& generator, const param_type& parameters) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `URng` | 无符号均匀随机位生成器，提供result_type、min()、max()和无参调用。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `generator` | 输入/输出 | 产生随机位；调用会推进其状态。 |
| `parameters` | 输入 | 原型2使用的分布区间参数，覆盖本次取样所用参数；不改变分布对象保存的参数。 |

原型1使用对象当前保存的参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `result_type` | 返回推进随机引擎后产生的下一个随机值。 |
| 原型2 | `result_type` | 返回推进随机引擎后产生的下一个随机值。 |

## 约束说明

- 支持全部标准整数结果类型。

## 调用示例

以下Host片段使用具体类型演示调用；输入范围和对象须在使用期间有效。

```cpp
#include <asc/std/random>

struct example_generator {
    using result_type = unsigned int;
    unsigned int state = 1;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return 2147483647u; }
    result_type operator()() { state = (state * 48271u) % 2147483647u; return state; }
};

decltype(auto) example()
{
    example_generator generator{};
    asc::std::uniform_int_distribution<int> distribution(0, 9);
    return distribution(generator);
}

bool verify_example()
{
    const auto result = example();
    return result >= 0 && result <= 9;
}
```

## 关联API

- [`asc::std::uniform_int_distribution`](uniform_int_distribution.md)
- [本头文件的接口列表](asc_std_random.md)
