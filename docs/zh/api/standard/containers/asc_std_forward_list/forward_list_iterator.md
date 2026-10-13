# asc::std::forward_list::iterator

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

`asc::std::forward_list::iterator`遍历对应容器元素的迭代器类型。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `forward_list`](https://en.cppreference.com/w/cpp/header/forward_list)。

## 声明

所属类型：[`asc::std::forward_list`](forward_list.md)。

```cpp
// asc::std::forward_list 类内的声明节选；模板形参和其他成员由所属类提供。
class iterator;
```

## 约束说明

- Host及AI Core SIMT编程下forward_list<T,A>显式GM arena allocator构造。
- empty/front/begin/end。
- push_front/emplace_front/pop_front/clear。
- 移动构造/赋值、移动前迭代器继续遍历目标节点及析构。
- 仅容量充足和不抛出异常值/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <memory>
#include <asc/std/forward_list>

template<class T>
struct ExampleAllocator : ::std::allocator<T> {
    using pointer = T*;
    using const_pointer = const T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template<class U> struct rebind { using other = ExampleAllocator<U>; };
    ExampleAllocator() = default;
    template<class U> ExampleAllocator(const ExampleAllocator<U>&) noexcept {}
};

bool example()
{
    using Container = asc::std::forward_list<int, ExampleAllocator<int>>;
    Container values(ExampleAllocator<int>{});
    values.push_front(4);
    values.push_front(2);
    auto it = values.begin();
    *it = 7;
    return values.front() == 7 && *++it == 4;
}
```

## 关联API

- [`asc::std::forward_list`](forward_list.md)
- [本头文件的接口列表](asc_std_forward_list.md)
