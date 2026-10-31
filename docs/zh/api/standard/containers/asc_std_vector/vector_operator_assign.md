# asc::std::vector::`operator=`

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

所属类型：[`asc::std::vector`](vector.md)。

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
vector<T, Allocator>& operator=(vector<T, Allocator>&& other) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `vector<T, Allocator> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 仅提供移动赋值，复制赋值已删除；自移动赋值不改变对象。
- 非自移动赋值先销毁目标元素并释放目标存储，再复制源分配器并接管源存储，使源容器变为空；不按分配器传播特征选择逐元素移动路径。
- 分配器赋值、元素销毁及存储释放操作须不抛出异常；目标原元素的指针、引用和迭代器失效。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/vector>
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
    using sequence = asc::std::vector<int, example_allocator<int>>;
    sequence values(example_allocator<int>{});
    values.push_back(7);
    sequence target(example_allocator<int>{});
    target = static_cast<sequence&&>(values);
    return !target.empty() && target.front() == 7;
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[explicit_allocator_vector.cpp](../../../../../../examples/standard/explicit_allocator_vector/main.cpp)。

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
