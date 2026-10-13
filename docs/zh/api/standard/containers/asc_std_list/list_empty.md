# asc::std::list::empty

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

头文件路径为：`<asc/std/list>`。

`asc::std::list::empty`判断当前对象是否不含元素。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `list`](https://en.cppreference.com/w/cpp/header/list)。

## 函数原型

所属类型：[`asc::std::list`](list.md)。

```cpp
// asc::std::list 类内的声明节选；模板形参和其他成员由所属类提供。
bool empty() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 对象不含元素时返回`true`，否则返回`false`。 |

## 约束说明

- Host及AI Core SIMT编程下list<T,A>显式GM arena allocator构造。
- empty/size/front/back/begin/end。
- push/emplace/pop_front/back/clear。
- 双向迭代核心、移动构造/赋值、移动前迭代器继续遍历目标节点及析构。
- 仅容量充足和不抛出异常值/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <memory>
#include <asc/std/list>

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
    asc::std::list<int, ExampleAllocator<int>> values(ExampleAllocator<int>{});
    values.push_back(1);
    values.push_back(3);
    return !values.empty();
}
```

## 关联API

- [`asc::std::list`](list.md)
- [本头文件的接口列表](asc_std_list.md)
