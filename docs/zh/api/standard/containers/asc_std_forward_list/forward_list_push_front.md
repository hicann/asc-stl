# asc::std::forward_list::push_front

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

头文件路径为：`<asc/std/forward_list>`。

`asc::std::forward_list::push_front`在容器首部插入一个元素。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `forward_list`](https://en.cppreference.com/w/cpp/header/forward_list)。

## 函数原型

所属类型：[`asc::std::forward_list`](forward_list.md)。

### 原型1

```cpp
// asc::std::forward_list 类内的声明节选；模板形参和其他成员由所属类提供。
void push_front(T&& value);
```

### 原型2

```cpp
// asc::std::forward_list 类内的声明节选；模板形参和其他成员由所属类提供。
void push_front(const T& value);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待插入到容器首部的元素值；以移动方式构造新元素，插入后新元素即链表首元素，源对象处于有效但未指定的移后状态。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待插入到容器首部的元素值；以复制方式构造新元素，插入后新元素即链表首元素，源对象保持不变。 |

## 返回值说明

无返回值。

## 约束说明

- Host及AI Core SIMT编程下forward_list<T,A>显式GM arena allocator构造。
- empty/front/begin/end。
- push_front/emplace_front/pop_front/clear。
- 移动构造/赋值、移动前迭代器继续遍历目标节点及析构。
- 仅容量充足和不抛出异常值/allocator域。
- Host和AI Core SIMT编程。

## 调用示例

以下Host片段使用显式提供的分配器；设备端须使用在目标执行位置可调用的分配器。

```cpp
#include <asc/std/forward_list>
#include <memory>

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
    using sequence = asc::std::forward_list<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.push_front(7);
    values.push_front(9);
    const bool first = !values.empty() && values.front() == 9;
    values.pop_front();
    const bool second = !values.empty() && values.front() == 7;
    values.pop_front();
    return first && second && values.empty();
}
```

## 关联API

- [`asc::std::forward_list`](forward_list.md)
- [本头文件的接口列表](asc_std_forward_list.md)
