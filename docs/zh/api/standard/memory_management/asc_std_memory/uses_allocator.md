# asc::std::uses_allocator

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

头文件路径为：`<asc/std/memory>`、`<asc/std/tuple>`。

`asc::std::uses_allocator`在编译期判断类型是否接受指定分配器构造。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<class T, class Allocator> struct uses_allocator;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/memory>`、`<asc/std/tuple>`。

### 原型2

```cpp
namespace asc::std {
template<class... T, class Allocator> struct uses_allocator<asc::std::tuple<T...>, Allocator>;
} // namespace asc::std
```

此原型对应头文件：`<asc/std/memory>`、`<asc/std/tuple>`。

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配。
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

struct Consumer { using allocator_type = ::std::allocator<int>; };

bool example()
{
    static_assert(asc::std::uses_allocator<Consumer, ::std::allocator<int>>::value);
    static_assert(!asc::std::uses_allocator<int, ::std::allocator<int>>::value);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
