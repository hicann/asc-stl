# asc::std::map::value_type

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

头文件路径为：`<asc/std/map>`。

`asc::std::map::value_type`标识元素或结果的值类型。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 声明

value_type是容器公开的键值条目类型。下面展示公开类型查询；entry_type只是示例别名。

```cpp
template<class Key, class T, class Compare, class Allocator>
using entry_type =
    typename asc::std::map<Key, T, Compare, Allocator>::value_type;
```

## 约束说明

- 条目具有`const Key first`与`T second`成员。
- 应使用容器的value_type构造条目；不能假定它与asc::std::pair<const Key, T>为同一类型。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/map>
#include <asc/std/type_traits>
#include <functional>
#include <memory>
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

using entry_type = typename asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>::value_type;
static_assert(asc::std::is_same_v<decltype(::std::declval<entry_type>().first), const int>);
static_assert(asc::std::is_same_v<decltype(::std::declval<entry_type>().second), int>);

bool example()
{
    const entry_type entry(7, 9);
    return entry.first == 7 && entry.second == 9;
}
```

## 关联API

- [`asc::std::map`](map.md)
- [本头文件的接口列表](asc_std_map.md)
