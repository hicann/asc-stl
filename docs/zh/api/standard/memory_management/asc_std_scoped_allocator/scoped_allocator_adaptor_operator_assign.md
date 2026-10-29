# asc::std::scoped_allocator_adaptor::`operator=`

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

头文件路径为：`<asc/std/scoped_allocator>`。

`asc::std::scoped_allocator_adaptor::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

所属类型：[`scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。以下仅说明隐式声明的赋值形式；是否定义为删除、是否为constexpr及其异常规格均按外层和内层分配器的C++特殊成员规则确定。

```cpp
scoped_allocator_adaptor& operator=(const scoped_allocator_adaptor& other);
scoped_allocator_adaptor& operator=(scoped_allocator_adaptor&& other);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 来源适配器；复制或移动其外层和内层分配器状态，元素存储本身不在本次操作中搬移。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `scoped_allocator_adaptor&` | 返回`*this`。 |

## 约束说明

- 赋值特殊成员按C++隐式声明规则由外层基类和内层分配器逐项赋值；可用性、常量求值和异常规格取决于这些成员。
- 本操作不读取传播特征来选择容器元素分配器，也不移动或复制任何已分配元素。

## 调用示例

以下Host片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

```cpp
#include <asc/std/scoped_allocator>
#include <functional>
#include <memory>
#include <string>
#include <utility>

template <class T>
struct example_allocator : ::std::allocator<T> {
    using value_type = T;
    int identity = 0;
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

void example(asc::std::scoped_allocator_adaptor<example_allocator<int>>& target, const asc::std::scoped_allocator_adaptor<example_allocator<int>>& source)
{
    target = source;
}

bool verify_example()
{
    asc::std::scoped_allocator_adaptor<example_allocator<int>> target, source;
    source.outer_allocator().identity = 23;
    example(target, source);
    int* value = target.allocate(1);
    if (value == nullptr) return false;
    target.construct(value, 7);
    const bool correct = *value == 7 && target.outer_allocator().identity == 23;
    target.destroy(value);
    target.deallocate(value, 1);
    return correct;
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
