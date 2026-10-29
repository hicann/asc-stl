# asc::std::vector::~vector

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

`asc::std::vector::~vector`销毁`vector`对象并结束其生命周期。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

```cpp
~vector();
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 析构销毁全部存活元素，再使用保存的分配器释放存储；元素析构和分配器释放操作须不抛出异常。
- 析构完成后，指向原元素的指针、引用及迭代器失效。
- 在Device侧析构时，元素析构和分配器释放操作须可用于相应编程模式。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
#include <memory>
#include <new>

struct allocation_counts {
    int allocated = 0;
    int released = 0;
};

template <class T>
struct counted_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U>
    struct rebind {
        using other = counted_allocator<U>;
    };
    allocation_counts* counts;
    explicit counted_allocator(allocation_counts& value) : counts(&value)
    {}
    template <class U>
    counted_allocator(const counted_allocator<U>& other) : counts(other.counts)
    {}
    T* allocate(::std::size_t count)
    {
        T* result = ::std::allocator<T>{}.allocate(count);
        ++counts->allocated;
        return result;
    }
    void deallocate(T* pointer, ::std::size_t count)
    {
        ::std::allocator<T>{}.deallocate(pointer, count);
        ++counts->released;
    }
};

bool example()
{
    allocation_counts counts;
    using sequence = asc::std::vector<int, counted_allocator<int>>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence(counted_allocator<int>(counts));
    values->push_back(7);
    const bool constructed = !values->empty() && values->front() == 7 && counts.allocated > 0;
    values->~sequence();
    return constructed && counts.allocated == counts.released;
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../examples/explicit_allocator_vector.cpp)。

## 关联API

- [本头文件的接口列表](asc_std_vector.md)
