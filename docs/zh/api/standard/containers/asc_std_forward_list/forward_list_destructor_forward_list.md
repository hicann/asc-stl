# asc::std::forward_list::~forward_list

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

头文件路径为：`<asc/std/forward_list>`。

`asc::std::forward_list::~forward_list`销毁`forward_list`对象并结束其生命周期。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `forward_list`](https://en.cppreference.com/w/cpp/header/forward_list)。

## 函数原型

```cpp
~forward_list();
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- Host及AI Core SIMT编程下forward_list<T,A>显式GM arena allocator构造。
- empty/front/begin/end。
- push_front/emplace_front/pop_front/clear。
- 移动构造/赋值、移动前迭代器继续遍历目标节点及析构。
- 仅容量充足和不抛出异常值/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下片段假定object指向已构造对象；显式析构后不得再次访问对象，存储释放由调用方负责。

```cpp
#include <asc/std/forward_list>
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
    using sequence = asc::std::forward_list<int, counted_allocator<int>>;
    alignas(sequence) unsigned char storage[sizeof(sequence)];
    auto* values = ::new (static_cast<void*>(storage)) sequence(counted_allocator<int>(counts));
    values->push_front(7);
    const bool constructed = !values->empty() && values->front() == 7 && counts.allocated > 0;
    values->~sequence();
    return constructed && counts.allocated == counts.released;
}
```

## 关联API

- [本头文件的接口列表](asc_std_forward_list.md)
