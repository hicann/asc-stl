# asc::std::optional

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

头文件路径为：`<asc/std/optional>`。

`asc::std::optional` 选择性地保存一个值。

标准语义参考：[cppreference `optional`](https://en.cppreference.com/w/cpp/header/optional)。

## 声明

### 原型 1

```cpp
template<class T> class asc::std::optional
```

### 原型 2

```cpp
template<class T> class asc::std::optional<T&>
```

## 约束说明

- T 必须是普通的非引用对象类型
- Host 遵循有效的 C++17 操作
- Device 侧构造、赋值、调用和交换所依赖的操作必须不抛出异常
- 引用特化仅允许安全的同类型左值绑定
- 采用借用指针语义，不提供容易产生悬空引用的转换

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/optional>

void use_type()
{
    using selected = asc::std::optional<int>;
    (void)sizeof(selected);
}
```
