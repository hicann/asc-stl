# asc::std::placeholders::_2

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

头文件路径为：`<asc/std/functional>`。

`asc::std::placeholders::_2`表示绑定表达式调用时的第2个实参占位符。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

以下为占位符对象声明；`__ph`是实现类型，调用方直接使用`placeholders::_2`，无需命名其类型。

```cpp
namespace asc::std::placeholders {
inline constexpr __ph<2> _2{};
}
```

## 约束说明

- 支持标准可调用对象和成员指针形式。

## 调用示例

以下Host示例用具体输入和可判断结果展示本接口。

```cpp
#include <asc/std/functional>

bool example()
{
    static_assert(asc::std::is_placeholder_v<decltype(asc::std::placeholders::_2)> == 2);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_functional.md)
