# asc::std::chrono::last_spec::last_spec

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

`asc::std::chrono::last_spec::last_spec`按本页所列构造形态初始化`last_spec`对象。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

last_spec是空标记类型；默认构造为显式，复制及移动由编译器隐式生成。

```cpp
explicit last_spec() = default;
```

## 参数说明

默认构造无参数。编译器生成的复制和移动构造接受另一个last_spec对象，仅复制空标签，不转移资源。

## 返回值说明

无返回值。

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::last_spec last{};
    auto date = asc::std::chrono::month{2} / last;
    return static_cast<unsigned int>(date.month()) == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
