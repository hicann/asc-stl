# asc::std::allocator_traits::allocate

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

`asc::std::allocator_traits::allocate` 向调用方提供的分配器申请对象存储。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr pointer asc::std::allocator_traits::allocate(allocator_type& allocator, size_type count);
```

### 原型 2

```cpp
[[nodiscard]] constexpr pointer asc::std::allocator_traits::allocate(allocator_type& allocator, size_type count, const_void_pointer hint);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `count` | 输入 | 参与操作的元素数量。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `count` | 输入 | 参与操作的元素数量。 |
| `hint` | 输入 | 提供“向调用方提供的分配器申请对象存储”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `pointer` | 返回分配器取得的存储地址；须按对应分配器规则释放。 |
| 原型 2 | `pointer` | 返回分配器取得的存储地址；须按对应分配器规则释放。 |

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
    asc::std::allocator_traits<example_allocator<int>>::deallocate(allocator, pointer, 1);
}
```
