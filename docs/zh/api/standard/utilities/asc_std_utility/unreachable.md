# asc::std::unreachable

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

头文件路径为：`<asc/std/utility>`。

`asc::std::unreachable`声明控制流不可能到达当前位置；违背前置条件属于未定义行为。

标准语义参考：[cppreference `utility`](https://en.cppreference.com/w/cpp/header/utility)。

## 函数原型

```cpp
namespace asc::std {
void unreachable();
} // namespace asc::std
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- to_underlying仅接受枚举类型。
- unreachable保留标准语义前置条件，但不添加当前工具链不支持的noreturn属性。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/utility>

void example()
{
    asc::std::unreachable();
}
```

## 关联API

- [本头文件的接口列表](asc_std_utility.md)
