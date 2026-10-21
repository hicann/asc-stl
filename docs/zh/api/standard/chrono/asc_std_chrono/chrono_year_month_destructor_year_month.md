# asc::std::chrono::year_month::~year_month

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

`asc::std::chrono::year_month::~year_month`销毁`year_month`对象并结束其生命周期。

标准语义参考：[cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono)。

## 函数原型

C++17形式如下；析构由编译器隐式生成，C++20起满足条件时可用于常量求值。

```cpp
~year_month() noexcept;
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 日历字段和计时值的运算可在Host与支持的AI Core编程模式使用；日期有效性由相应`ok()`成员判断。

## 调用示例

以下片段假定object指向已构造对象；显式析构后不得再次访问对象，存储释放由调用方负责。

```cpp
#include <asc/std/chrono>

using example_object = asc::std::chrono::year_month;
void example(example_object* object)
{
    // object 指向已构造对象；析构后不得再访问该对象。
    object->~example_object();
}
```

## 关联API

- [本头文件的接口列表](asc_std_chrono.md)
