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

`asc::std::uses_allocator` 在编译期判断类型是否接受指定分配器构造。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

### 原型 1

```cpp
template<class ...T, class Allocator> struct asc::std::uses_allocator
```

此原型对应头文件：`<asc/std/memory>`、`<asc/std/tuple>`。

### 原型 2

```cpp
template<class T, class Allocator> struct asc::std::uses_allocator
```

此原型对应头文件：`<asc/std/memory>`、`<asc/std/tuple>`。

## 约束说明

- 构造、赋值、交换及相关自由函数均不进行动态内存分配
- allocator_arg_t/allocator_arg
- uses_allocator/uses_allocator_v
- allocator_traits 的 C++20 成员类型、rebind、allocate/deallocate、construct/destroy、max_size、select_on_container_copy_construction
- uses_allocator_construction_args/make_obj_using_allocator/uninitialized_construct_using_allocator 含 pair 递归构造
- C++23 allocation_result 与标准 allocator_traits::allocate_at_least
- 均限用户显式提供且在调用执行空间有效的 allocator

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/memory>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <deque>
#include <functional>
#include <vector>

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
    using selected = asc::std::uses_allocator<::std::vector<int, example_allocator<int>>, example_allocator<int>>;
    (void)sizeof(selected);
}
```
