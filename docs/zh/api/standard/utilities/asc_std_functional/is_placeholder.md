# asc::std::is_placeholder

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

`asc::std::is_placeholder` 在编译期识别绑定表达式或参数占位符。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 声明

```cpp
template<class T> struct asc::std::is_placeholder
```

结果语义：主模板对非占位符类型继承 `asc::std::integral_constant<int, 0>`；对占位符类型（`asc::std::placeholders::_1` 至 `_10`），经特化继承 `asc::std::integral_constant<int, N>`，其中 `N` 为对应占位符的调用实参位置（`N >= 1`）。占位符实现模板参数（`int N`）不属于公共主模板参数。

## 约束说明

- 支持标准可调用对象和成员指针形式
- invoke_r 为 C++23 回移提供的接口

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/functional>

void use_type()
{
    using selected = asc::std::is_placeholder<int>;
    (void)sizeof(selected);
}
```
