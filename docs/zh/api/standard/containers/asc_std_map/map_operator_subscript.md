# asc::std::map::operator[]

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

`asc::std::map::operator[]` 按键查找映射值：键已存在时返回对应映射值的引用；键不存在时向容器插入由该键和默认构造的映射值组成的元素，并返回新插入元素映射值的引用。

执行插入要求映射值类型可默认构造；节点分配或元素构造失败、抛出异常时容器内容保持不变。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `map`](https://en.cppreference.com/w/cpp/header/map)。

## 函数原型

```cpp
T& asc::std::map::operator[](const Key& key);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `key` | 输入 | 提供“按键查找映射值并在键不存在时插入元素”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T &` | 键已存在时返回对应映射值的引用；键不存在时返回新插入元素映射值的引用。 |

## 约束说明

- Host及AI Core SIMT 编程下map<Key,T,Compare,A>显式GM arena
- allocator以及Compare+allocator构造
- empty/size/begin/end/insert/find/count/operator[]/clear
- AVL平衡与对数级插入/查找核心
- 重复键拒绝、有序迭代、移动和析构
- 仅容量充足和不抛出异常键值/比较/allocator域
- Host 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

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
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

decltype(auto) example(asc::std::map<int, int, ::std::less<int>, example_allocator<::std::pair<const int, int>>>& values)
{
    return values[7];
}
```
