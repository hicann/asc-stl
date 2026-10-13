# asc::std::pointer_traits::rebind

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

头文件路径为：`<asc/std/memory>`。

`asc::std::pointer_traits::rebind`按给定元素类型重新绑定分配器或指针特征。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

所属类型：[`asc::std::pointer_traits`](pointer_traits.md)。

```cpp
// asc::std::pointer_traits 类内的声明节选；模板形参和其他成员由所属类提供。
template<class U> using rebind = U*;
```

## 约束说明

- 支持原始指针和用户自定义fancy pointer，接口自身不分配内存。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/memory>

template <class Ptr, class U>
void use_type()
{
    using alias_type = typename asc::std::pointer_traits<Ptr>::rebind<U>;
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[pointer_alignment.cpp](../../../../examples/pointer_alignment.cpp)。

## 关联API

- [`asc::std::pointer_traits`](pointer_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
