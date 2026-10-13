# asc::std::make_obj_using_allocator

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

`asc::std::make_obj_using_allocator`按uses-allocator规则构造并返回对象。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<class T, class Alloc, class... Args> constexpr T make_obj_using_allocator(const Alloc& alloc, Args&&... args);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |
| `Alloc` | 为对象或元素分配和释放存储的分配器类型。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `alloc` | 输入 | 提供“按uses-allocator规则构造并返回对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回对象。 |

## 约束说明

- T必须能够按分配器感知构造规则使用allocator和args... 完成构造。
- allocator以及args... 引用的对象必须在调用期间保持有效。
- Alloc必须能够在当前调用所在的执行空间中使用。
- 调用参数必须满足所选T构造函数的前置条件。

## 调用示例

以下Host片段使用有效对象或对齐存储；构造后的对象在示例末尾销毁。

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

decltype(auto) example()
{
    example_allocator<int> allocator;
    return asc::std::make_obj_using_allocator<int>(allocator, 7);
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
