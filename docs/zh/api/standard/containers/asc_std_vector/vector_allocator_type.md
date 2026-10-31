# asc::std::vector::allocator_type

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

`asc::std::vector::allocator_type`标识当前对象使用的分配器类型。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 声明

所属类型：[`asc::std::vector`](vector.md)。

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
using allocator_type = Allocator;
```

## 约束说明

- 该别名为容器的模板参数`Allocator`；读取类型本身不进行分配。
- 分配器及元素操作的调用条件见所属类型[vector](vector.md)。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
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
    template <class U>
    struct rebind {
        using other = example_allocator<U>;
    };
    example_allocator() = default;
    template <class U>
    example_allocator(const example_allocator<U>&) noexcept
    {}
};
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::vector<int, example_allocator<int>>::allocator_type;
static_assert(::std::is_same_v<alias_type, example_allocator<int>>);
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../../../examples/standard/explicit_allocator_vector/main.cpp)。

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
