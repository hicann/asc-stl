# asc::std::allocator_traits::propagate_on_container_move_assignment

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

`asc::std::allocator_traits::propagate_on_container_move_assignment`标识对应容器复制、移动或交换操作是否传播分配器。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

`asc::std::allocator_traits<Allocator>::propagate_on_container_move_assignment`优先使用Allocator自身的同名成员类型；否则为false_type。

```cpp
template<class Allocator>
using selected = typename asc::std::allocator_traits<Allocator>::propagate_on_container_move_assignment;
```

## 约束说明

- 本页是分配器特征的编译期类型查询，不分配存储或构造对象。
- 对应成员的提取及缺省规则见[`allocator_traits`](allocator_traits.md)；具体分配器须满足所查询的成员或重绑定形式要求。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

using selected = typename asc::std::allocator_traits<example_allocator<int>>::propagate_on_container_move_assignment;

static_assert(selected::value == true);
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[allocator_traits.cpp](../../../../examples/allocator_traits.cpp)。

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
