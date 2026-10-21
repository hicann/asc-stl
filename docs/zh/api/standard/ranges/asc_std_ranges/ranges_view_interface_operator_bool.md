# asc::std::ranges::view_interface::operator bool

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::view_interface::operator bool`由`<asc/std/ranges>`提供，视图接口的显式布尔转换，经判空定制点对象判断区间是否为空。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`view_interface<Derived>`](ranges_view_interface.md)。以下为省略SFINAE选择参数的声明摘要；两个形式分别在ranges::empty可用于Derived&和const Derived&时参与。

```cpp
template<class Derived2 = Derived>
constexpr explicit operator bool();

template<class Derived2 = Derived>
constexpr explicit operator bool() const;
```

## 参数说明

无函数参数；Derived2默认为Derived，用于延迟检查相应const形式的empty查询。

## 返回值说明

非空时返回true，空时返回false；转换为explicit，可用于if条件或显式static_cast<bool>。

## 约束说明

- 相应const形式的ranges::empty查询须有效；本转换只检查是否为空，不取得元素所有权。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator bool(static_cast<Args&&>(args)...);
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
