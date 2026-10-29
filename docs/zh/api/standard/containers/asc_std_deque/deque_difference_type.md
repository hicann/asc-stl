# asc::std::deque::difference_type

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

头文件路径为：`<asc/std/deque>`。

`asc::std::deque::difference_type`标识迭代器距离的有符号类型。

标准语义参考：[cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque)。

## 声明

所属类型：[`asc::std::deque`](deque.md)。

```cpp
// asc::std::deque 类内的声明节选；模板形参和其他成员由所属类提供。
using difference_type = long;
```

## 约束说明

- deque<T,A>显式allocator构造。
- 有限块映射内的push/emplace/pop_front/back。
- empty/size/front/back/`operator[]`/随机访问迭代核心。
- 新端块分配时已有元素引用稳定。
- clear/析构。
- 仅容量充足和不抛出异常域。

## 调用示例

以下Host片段显式提供带重绑定能力的分配器；设备端须改用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/deque>
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

using alias_type = typename asc::std::deque<int, example_allocator<int>>::difference_type;
static_assert(::std::is_same_v<alias_type, ::std::ptrdiff_t>);
```

## 关联API

- [`asc::std::deque`](deque.md)
- [本头文件的接口列表](asc_std_deque.md)
