# asc::std::allocator_traits::destroy

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

`asc::std::allocator_traits::destroy` 结束指定地址处单个对象的生命周期：优先调用分配器的 `destroy` 成员，分配器未提供该成员时回退为调用指针所指对象的析构函数（等价于 `pointer->~T()`）。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
template<class T> constexpr void asc::std::allocator_traits::destroy(allocator_type& allocator, T* pointer) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `pointer` | 输入 | 提供“结束指定地址处单个对象的生命周期”所需的数据地址；可访问范围和生命周期须满足约束。 |

## 返回值说明

无返回值。

## 约束说明

- allocator_arg_t/allocator_arg
- uses_allocator/uses_allocator_v
- allocator_traits 的 C++20 成员类型、rebind、allocate/deallocate、construct/destroy、max_size、select_on_container_copy_construction
- uses_allocator_construction_args/make_obj_using_allocator/uninitialized_construct_using_allocator 含 pair 递归构造
- C++23 allocation_result 与标准 allocator_traits::allocate_at_least
- 均限用户显式提供且在调用执行空间有效的 allocator

## 调用示例

以下 Host 片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

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

void example(example_allocator<int>& allocator)
{
    int* pointer = asc::std::allocator_traits<example_allocator<int>>::allocate(allocator, 1);
    asc::std::allocator_traits<example_allocator<int>>::construct(allocator, pointer, 7);
    asc::std::allocator_traits<example_allocator<int>>::destroy(allocator, pointer);
    asc::std::allocator_traits<example_allocator<int>>::deallocate(allocator, pointer, 1);
}
```
