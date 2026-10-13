# asc::std::allocator_traits

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

`asc::std::allocator_traits`统一访问分配器的类型、分配和对象构造操作。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

```cpp
namespace asc::std {
template<class Allocator> struct allocator_traits;
} // namespace asc::std
```

## 约束说明

- allocator_arg_t/allocator_arg。
- uses_allocator/uses_allocator_v。
- allocator_traits的C++20成员类型、rebind、allocate/deallocate、construct/destroy、max_size、select_on_container_copy_construction。
- uses_allocator_construction_args/make_obj_using_allocator/uninitialized_construct_using_allocator含pair递归构造。
- C++23 allocation_result与标准allocator_traits::allocate_at_least。
- 均限用户显式提供且在调用执行空间有效的allocator。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/memory>

bool example()
{
    using Allocator = ::std::allocator<int>;
    using Traits = asc::std::allocator_traits<Allocator>;
    Allocator allocator;
    int* pointer = Traits::allocate(allocator, 1);
    Traits::construct(allocator, pointer, 7);
    const bool passed = *pointer == 7;
    Traits::destroy(allocator, pointer);
    Traits::deallocate(allocator, pointer, 1);
    return passed;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
