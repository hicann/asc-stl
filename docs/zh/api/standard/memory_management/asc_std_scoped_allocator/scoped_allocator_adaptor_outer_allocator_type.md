# asc::std::scoped_allocator_adaptor::outer_allocator_type

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

`asc::std::scoped_allocator_adaptor::outer_allocator_type`标识外层存储分配器类型。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 声明

所属类型：[`scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。

```cpp
using outer_allocator_type = OuterAllocator;
```

## 约束说明

- 此类型由外层或保存的内层分配器直接确定，不用不存在的`outer_traits`别名补齐类型。
- 类型查询不访问元素或改变分配器状态；实际操作要求见适配器及对应成员页。

## 调用示例

以下Host片段显式提供带重绑定能力的分配器；设备端须改用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/scoped_allocator>
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

using selected = typename asc::std::scoped_allocator_adaptor<example_allocator<int>>::outer_allocator_type;

static_assert(asc::std::is_same_v<selected, example_allocator<int>>);
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
