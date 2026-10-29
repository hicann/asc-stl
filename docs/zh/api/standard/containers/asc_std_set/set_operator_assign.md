# asc::std::set::`operator=`

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

头文件路径为：`<asc/std/set>`。

`asc::std::set::operator=`按所选赋值重载更新对象，并返回规定的结果。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `set`](https://en.cppreference.com/w/cpp/header/set)。

## 函数原型

所属类型：[`asc::std::set`](set.md)。

```cpp
// asc::std::set 类内的声明节选；模板形参和其他成员由所属类提供。
set<Key, Compare, Allocator>& operator=(set<Key, Compare, Allocator>&& other) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `set<Key, Compare, Allocator> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- Host及AI Core SIMT编程下set<Key,Compare,A>显式GM arena。
- allocator以及Compare+allocator构造。
- empty/size/begin/end/insert/find/count/clear。
- AVL平衡与对数级插入/查找核心。
- 重复键拒绝、有序迭代、移动和析构。
- 仅容量充足和不抛出异常键/比较/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/set>
#include <memory>
#include <functional>
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

bool example()
{
    using sequence = asc::std::set<int, ::std::less<int>, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.insert(7);
    sequence target(example_allocator<int>{});
    target = static_cast<sequence&&>(values);
    return target.size() == 1 && *target.find(7) == 7;
}
```

## 关联API

- [`asc::std::set`](set.md)
- [本头文件的接口列表](asc_std_set.md)
