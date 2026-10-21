# asc::std::numbers::phi_v

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

`asc::std::numbers::phi_v`由`<asc/std/numbers>`提供，提供`phi_v`常量或变量。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers)。

## 声明

```cpp
namespace asc::std::numbers {
template<class Tp> inline constexpr Tp phi_v = __numbers<Tp>::__phi();
}
```

## 约束说明

- 提供float变量模板。
- 黄金比变量模板，同上边界。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/numbers>

constexpr float value = asc::std::numbers::phi_v<float>;
static_assert(value > 1.61f && value < 1.62f);
```

## 关联API

- [本头文件的接口列表](asc_std_numbers.md)
