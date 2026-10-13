# asc::std::unordered_set::`operator=`

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

头文件路径为：`<asc/std/unordered_set>`。

`asc::std::unordered_set::operator=`按所选赋值重载更新对象，并返回规定的结果。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set)。

## 函数原型

所属类型：[`asc::std::unordered_set`](unordered_set.md)。

```cpp
// asc::std::unordered_set 类内的声明节选；模板形参和其他成员由所属类提供。
unordered_set<Key, Hash, Equal, Allocator>& operator=(unordered_set<Key, Hash, Equal, Allocator>&& other) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `unordered_set<Key, Hash, Equal, Allocator> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- Host及AI Core SIMT编程下unordered_set<Key,Hash,Equal,A>显式GM arena。
- empty/size/bucket_count/begin/end/insert/find/count/clear。
- allocator回绑桶数组并在默认负载阈值上自动rehash。
- 碰撞链、重复键拒绝、rehash节点地址稳定、移动后旧迭代器有效与析构。
- 仅容量充足和不抛出异常域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/unordered_set>
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
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

void example(asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>& target, asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>& source)
{
    target = static_cast<asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>&&>(source);
}
```

## 关联API

- [`asc::std::unordered_set`](unordered_set.md)
- [本头文件的接口列表](asc_std_unordered_set.md)
