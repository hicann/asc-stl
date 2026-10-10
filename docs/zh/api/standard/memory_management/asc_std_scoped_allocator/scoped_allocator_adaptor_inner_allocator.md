# asc::std::scoped_allocator_adaptor::inner_allocator

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

`asc::std::scoped_allocator_adaptor::inner_allocator` 返回内部元素构造使用的分配器。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

### 原型 1

```cpp
constexpr const inner_allocator_type& asc::std::scoped_allocator_adaptor::inner_allocator() const noexcept;
```

### 原型 2

```cpp
constexpr inner_allocator_type& asc::std::scoped_allocator_adaptor::inner_allocator() noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

无参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `const inner_allocator_type &` | 返回内部元素构造使用的分配器。 |
| 原型 2 | `inner_allocator_type &` | 返回内部元素构造使用的分配器。 |

## 约束说明

- 遵循 scoped_allocator_adaptor 的标准分配器传播、构造、销毁、比较和交换约束
- 参与操作的分配器必须在当前可用位置有效，Device 侧操作不得抛出异常

## 调用示例

以下 Host 片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

```cpp
#include <asc/std/scoped_allocator>
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

decltype(auto) example(asc::std::scoped_allocator_adaptor<example_allocator<int>>& allocator)
{
    return allocator.inner_allocator().outer_allocator();
}
```
