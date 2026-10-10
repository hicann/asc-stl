# asc::std::ranges::in_fun_result

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::ranges::in_fun_result<Iter, Func>` 从 C++17 起保存算法结束迭代器 `in` 和执行后的函数对象 `fun`。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 声明

### 原型 1

```cpp
template<class Iter, class Func> struct asc::std::ranges::in_fun_result
```

### 原型 2

```cpp
template<class InIter1, class Func1> struct asc::std::ranges::in_fun_result
```

## 约束说明

- 遵循该接口声明对应的类型和前置条件
- 调用方必须保证实参取值、对象生命周期、地址空间及可用位置有效

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/algorithm>

void use_type()
{
    using selected = asc::std::ranges::in_fun_result<int*, int (*)(int)>;
    (void)sizeof(selected);
}
```
