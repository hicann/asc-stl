# asc::std::allocator_traits::select_on_container_copy_construction

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

`asc::std::allocator_traits::select_on_container_copy_construction`选择复制构造容器时应使用的分配器。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

所属类型：[`asc::std::allocator_traits`](allocator_traits.md)。

```cpp
// asc::std::allocator_traits 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr allocator_type select_on_container_copy_construction(const allocator_type& allocator);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入 | 负责对象存储分配与释放的分配器。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `allocator_type` | 返回复制构造容器时应采用的分配器。 |

## 约束说明

- 分配器提供可调用的同名选择成员时使用其返回值，否则按值复制传入的分配器。
- 查询不复制或构造容器元素；返回分配器对象的所有权及资源共享规则由其类型决定。

## 调用示例

以下Host片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

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

using selected = decltype(asc::std::allocator_traits<example_allocator<int>>::select_on_container_copy_construction(asc::std::declval<const example_allocator<int>&>()));

static_assert(asc::std::is_same_v<selected, example_allocator<int>>);
```

## 关联API

- [`asc::std::allocator_traits`](allocator_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
