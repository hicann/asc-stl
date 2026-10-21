# asc::std::chrono::duration

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

头文件路径为：`<asc/std/chrono>`。

`asc::std::chrono::duration`把计数`Rep`与每个tick对应的秒比例`Period`组合为时长；跨周期运算先形成公共计时单位。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 声明

```cpp
namespace asc::std::chrono {
template<class Rep, class Period = ratio<1>> class duration;
} // namespace asc::std::chrono
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Rep` | 保存tick数量的计数类型；不能为duration。 |
| `Period` | 每tick对应秒数的正ratio类型，默认为ratio<1>。 |

## 约束说明

- Rep不得为duration；Period须为ratio特化，且Period::num须为正。
- 算术及中间值须可表示；取模还要求计数支持余数运算。
- 内建计数的默认初始化不保证为0；读取count()前应使用明确计数初始化，例如seconds{0}。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::seconds value(3);
    const auto milliseconds = asc::std::chrono::duration_cast<asc::std::chrono::milliseconds>(value);
    return value.count() == 3 && milliseconds.count() == 3000;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
