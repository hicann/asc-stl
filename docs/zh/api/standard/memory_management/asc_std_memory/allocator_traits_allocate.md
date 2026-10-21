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

`asc::std::allocator_traits::allocate`向调用方提供的分配器申请对象存储。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

所属类型：[`asc::std::allocator_traits`](allocator_traits.md)。

### 原型1

```cpp
// asc::std::allocator_traits 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr pointer allocate(allocator_type& allocator, size_type count);
```

### 原型2

```cpp
// asc::std::allocator_traits 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr pointer allocate(allocator_type& allocator, size_type count, const_void_pointer hint);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `count` | 输入 | 待申请存储可容纳的元素个数，按count个value_type对象申请。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `count` | 输入 | 待申请存储可容纳的元素个数，按count个value_type对象申请。 |
| `hint` | 输入 | 局部性提示地址，通常取自同一分配器先前返回的指针；可为空，分配器可忽略。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pointer` | 返回分配器取得的存储地址；须按对应分配器规则释放。 |
| 原型2 | `pointer` | 返回分配器取得的存储地址；须按对应分配器规则释放。 |

## 约束说明

- 向给定分配器申请`count`个`value_type`的未初始化存储，不构造元素。
- 提示形式在分配器接受`hint`时传递它，否则忽略提示并调用单参数`allocate`。
- 数量、执行位置、分配失败行为和后续释放规则由分配器约定。

## 调用示例

以下Host片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

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

## 关联API

- [`asc::std::allocator_traits`](allocator_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
