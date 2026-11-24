# asc::std::map::iterator

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

`asc::std::map::iterator` 是前向迭代器，按键比较器确定的顺序遍历键值对。当 `it` 可解引用时，`it++` 返回递增前的迭代器副本，并将 `it` 移到下一项或 `end()`。键（`it->first`）只读，映射值（`it->second`）可修改。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 声明

所属类型：[`asc::std::map`](map.md)。

```cpp
// asc::std::map 类内的声明节选；模板形参和其他成员由所属类提供。
using iterator = typename tree_type::iterator;
```

## 约束说明

- Host及AI Core SIMT编程下map<Key,T,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/`operator[]`/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键值/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host片段显式提供带重绑定能力的分配器；设备端须改用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/map>
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

using alias_type =
    typename asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>::iterator;
static_assert(::std::is_same_v<alias_type,
    decltype(::std::declval<
             asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>&>()
                 .begin())>);
```

## 关联API

- [`asc::std::map`](map.md)
- [本头文件的接口列表](asc_std_map.md)
