# asc::std::scoped_allocator_adaptor::select_on_container_copy_construction

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：本页为兼容性说明，所述接口未提供
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

本页保留原入口用于兼容性说明。适配器自身没有`select_on_container_copy_construction()`成员；也不递归选择内层分配器。外层同名成员可能通过继承可见，但不能据此当成返回完整适配器的成员。

普通复制可直接复制适配器对象；若需要外层分配器的复制选择，请显式对外层类型使用`allocator_traits`，并自行处理内层分配器。

## 函数原型

当前产品不声明本页标题所示的接口。请使用下述已提供的接口。

## 参数说明

本页不声明可调用的接口参数。

## 返回值说明

本页不声明接口返回值；替代调用的结果见调用示例。

## 约束说明

- 适配器自身没有`select_on_container_copy_construction()`成员；也不递归选择内层分配器。外层同名成员可能通过继承可见，但不能据此当成返回完整适配器的成员。
- 普通复制可直接复制适配器对象；若需要外层分配器的复制选择，请显式对外层类型使用`allocator_traits`，并自行处理内层分配器。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    const adaptor source(example_allocator<int>{7});
    const adaptor copied(source);
    return copied.outer_allocator().identity == 7;
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
