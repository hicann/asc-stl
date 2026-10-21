# asc::std::numbers::e

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

`asc::std::numbers::e`提供自然对数的底的编译期值。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `numbers`](https://en.cppreference.com/w/cpp/header/numbers)。

## 声明

```cpp
namespace asc::std::numbers {
inline constexpr double e = 0x1.5bf0a8b1457695355fb8ac404e7ap+1;
}
```

## 约束说明

- 13个标准double命名常量。
- 可用于Host与D-SIMT；参与操作的对象及其存储须在对应执行位置有效。
- 普通AICore仅constant-fold后无runtime double的用法。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/numbers>

auto value = asc::std::numbers::e;
```

## 关联API

- [本头文件的接口列表](asc_std_numbers.md)
