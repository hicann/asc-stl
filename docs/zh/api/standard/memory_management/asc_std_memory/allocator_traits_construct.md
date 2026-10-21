# asc::std::allocator_traits::construct

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

`asc::std::allocator_traits::construct`在已分配存储中按给定参数构造对象。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

所属类型：[`asc::std::allocator_traits`](allocator_traits.md)。

```cpp
// asc::std::allocator_traits 类内的声明节选；模板形参和其他成员由所属类提供。
template<class T, class ...Args> static constexpr void construct(allocator_type& allocator, T* pointer, Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `allocator` | 输入/输出 | 负责对象存储分配与释放的分配器。 |
| `pointer` | 输出 | 满足目标对象大小与对齐的未初始化存储地址；调用在该处开始对象生命周期，构造实参决定其初值。 |
| `args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

无返回值。

## 约束说明

- `pointer`须提供足够且正确对齐的未初始化存储。实参按原值类别转发。
- 优先调用分配器可用的`construct`成员，否则直接在该地址构造`T`；不会自行执行uses-allocator参数注入。
- Device使用须保证对应构造和分配器操作可在该位置调用且不抛出异常。

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
    asc::std::allocator_traits<example_allocator<int>>::construct(allocator, pointer, 7);
    asc::std::allocator_traits<example_allocator<int>>::destroy(allocator, pointer);
    asc::std::allocator_traits<example_allocator<int>>::deallocate(allocator, pointer, 1);
}
```

## 关联API

- [`asc::std::allocator_traits`](allocator_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
