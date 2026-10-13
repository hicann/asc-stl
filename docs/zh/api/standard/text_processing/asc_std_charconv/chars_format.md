# asc::std::chars_format

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

头文件路径为：`<asc/std/charconv>`。

`asc::std::chars_format`由`<asc/std/charconv>`提供，[charconv.syn] 格式词表位掩码枚举，枚举值独立于宿主标准库，hosted与设备编译共享同一表示

标准语义参考：[cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv)。

## 声明

```cpp
enum class chars_format { scientific = 0x1, fixed = 0x2, hex = 0x4, general = fixed | scientific };
```

## 约束说明

- [charconv.syn] 格式词表位掩码枚举，枚举值独立于宿主标准库，hosted与设备编译共享同一表示。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/charconv>

decltype(auto) example()
{
    return asc::std::chars_format();
}
```

## 关联API

- [本头文件的接口列表](asc_std_charconv.md)
