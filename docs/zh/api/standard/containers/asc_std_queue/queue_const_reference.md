# asc::std::queue::const_reference

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

头文件路径为：`<asc/std/queue>`。

`asc::std::queue::const_reference` 标识只读元素引用类型。

标准语义参考：[cppreference `queue`](https://en.cppreference.com/w/cpp/header/queue)。

## 声明

```cpp
using asc::std::queue::const_reference = typename Container::const_reference
```

## 约束说明

- queue<T,Container>的显式兼容Container合同：T必须等于Container::value_type，Container的构造/front/back/push_back/emplace_back/pop_front/比较/swap及allocator操作必须在当前执行空间有效
- 交付container_type/value_type/size_type/reference/const_reference和protected c，default/container/copy/move/allocator构造及copy/move赋值，empty/size/front/back、lvalue/rvalue push、decltype(auto) emplace、pop，条件noexcept的member/non-member swap，六个经典关系与C++20 <=>，uses_allocator特化，Container及Container+Alloc的C++17 CTAD
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段显式提供标准容器作为底层存储；设备端须提供可在目标位置调用的容器。

```cpp
#include <asc/std/queue>
#include <deque>
#include <functional>
#include <vector>

void use_type()
{
    using alias_type = typename asc::std::queue<int, ::std::deque<int>>::const_reference;
}
```
