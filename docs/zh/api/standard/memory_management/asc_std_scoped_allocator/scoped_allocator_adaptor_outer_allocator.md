# asc::std::scoped_allocator_adaptor::outer_allocator

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

头文件路径为：`<asc/std/scoped_allocator>`。

`asc::std::scoped_allocator_adaptor::outer_allocator`返回容器自身存储使用的外层分配器。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

所属类型：[`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。

### 原型1

```cpp
// asc::std::scoped_allocator_adaptor 类内的声明节选；模板形参和其他成员由所属类提供。
const outer_allocator_type& outer_allocator() const noexcept;
```

### 原型2

```cpp
// asc::std::scoped_allocator_adaptor 类内的声明节选；模板形参和其他成员由所属类提供。
outer_allocator_type& outer_allocator() noexcept;
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `const outer_allocator_type &` | 返回容器自身存储使用的外层分配器。 |
| 原型2 | `outer_allocator_type &` | 返回容器自身存储使用的外层分配器。 |

## 约束说明

- 返回外层分配器基类子对象的引用，不复制状态或转移所有权；适配器须覆盖该引用的使用期。

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
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.outer_allocator().identity == 7 && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
