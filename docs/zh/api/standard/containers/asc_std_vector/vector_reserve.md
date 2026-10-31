# asc::std::vector::reserve

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector::reserve`请求至少可容纳指定数量元素的存储容量。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

所属类型：[`asc::std::vector`](vector.md)。

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
void reserve(size_type requested);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `requested` | 输入 | 请求的最小容量，单位为元素个数；大于当前capacity()时重分配存储使容量不小于该值，否则容量不变；不得超过max_size()。 |

## 返回值说明

无返回值。

## 约束说明

- `T`须能由`T&&`构造并可析构，以满足当前实现迁移元素的编译要求；即使本次不扩容，也须满足该类型要求。
- `requested <= capacity()`时不分配；否则分配新存储并逐元素迁移原元素。
- 成功扩容不改变`size()`，但会使原存储上的指针、引用及迭代器失效。
- Host侧分配器返回空指针时抛出`std::bad_alloc`；分配器或元素移动构造抛出的异常可传播。Device侧须保证相关操作可调用且不抛出异常，并保证分配成功，分配失败会终止执行。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
#include <memory>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};

bool example()
{
    using sequence = asc::std::vector<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.push_back(7);
    values.reserve(16);
    return values.capacity() >= 16 && values.size() == 1 && values[0] == 7;
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../../../examples/standard/explicit_allocator_vector/main.cpp)。

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
