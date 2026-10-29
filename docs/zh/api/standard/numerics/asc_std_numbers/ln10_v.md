# asc::std::ln10_v

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

头文件路径为：`<asc/std/numbers>`。

`asc::std::ln10_v`提供10的自然对数的编译期值。

标准语义参考：[cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers)。

## 声明

```cpp
namespace asc::std {
template<class Tp> inline constexpr Tp ln10_v = __numbers<Tp>::__ln10();
}
```

## 约束说明

- 提供float变量模板。

## 调用示例

以下片段用具体模板实参读取接口值。

```cpp
#include <asc/std/numbers>

inline constexpr auto example = asc::std::ln10_v<float>;
static_assert(example > 2.3025849 && example < 2.3025852);
```

## 关联API

- [本头文件的接口列表](asc_std_numbers.md)
