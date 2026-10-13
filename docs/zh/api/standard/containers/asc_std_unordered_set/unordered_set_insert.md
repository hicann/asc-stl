# asc::std::unordered_set::insert

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

`asc::std::unordered_set::insert`在指定位置插入元素并按容器规则更新迭代器。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `unordered_set`](https://en.cppreference.com/w/cpp/header/unordered_set)。

## 函数原型

所属类型：[`asc::std::unordered_set`](unordered_set.md)。

### 原型1

```cpp
// asc::std::unordered_set 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(Key&& key);
```

### 原型2

```cpp
// asc::std::unordered_set 类内的声明节选；模板形参和其他成员由所属类提供。
pair<iterator, bool> insert(const Key& key);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `key` | 输入/输出 | 提供“在指定位置插入元素并按容器规则更新迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `key` | 输入 | 提供“在指定位置插入元素并按容器规则更新迭代器”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `pair<iterator, bool>` | 返回指向该键元素的迭代器及是否新插入的bool；键已存在时bool为false。 |
| 原型2 | `pair<iterator, bool>` | 返回指向该键元素的迭代器及是否新插入的bool；键已存在时bool为false。 |

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

decltype(auto) example(asc::std::unordered_set<int, ::std::hash<int>, ::std::equal_to<int>, example_allocator<int>>& values)
{
    return values.insert(7);
}
```

## 关联API

- [`asc::std::unordered_set`](unordered_set.md)
- [本头文件的接口列表](asc_std_unordered_set.md)
