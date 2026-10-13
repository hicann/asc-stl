# asc::std::allocator_traits::void_pointer

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

`asc::std::allocator_traits::void_pointer`标识分配器可表示的void指针类型。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

`asc::std::allocator_traits<Allocator>::void_pointer`是成员类型别名。

若Allocator提供void_pointer，则采用该类型；否则由pointer_traits<pointer>::rebind<void> 得到。

在依赖类型上下文中按以下形式使用：

```cpp
template<class Allocator>
using selected_void_pointer = typename asc::std::allocator_traits<Allocator>::void_pointer;
```

## 约束说明

- 若Allocator提供void_pointer，则采用该类型；否则由pointer_traits<pointer>::rebind<void> 得到。
- `Allocator`是调用方显式提供的分配器类型；本成员类型查询不执行分配。

## 调用示例

以下Host片段显式提供带重绑定能力的分配器；设备端须改用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/memory>
#include <functional>
#include <memory>
#include <string>
#include <utility>

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

void use_type()
{
    using alias_type = typename asc::std::allocator_traits<example_allocator<int>>::void_pointer;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
