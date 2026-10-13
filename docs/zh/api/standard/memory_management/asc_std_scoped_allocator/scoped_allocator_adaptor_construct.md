# asc::std::scoped_allocator_adaptor::construct

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

`asc::std::scoped_allocator_adaptor::construct`在已分配存储中按给定参数构造对象。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

所属类型：[`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。

```cpp
// asc::std::scoped_allocator_adaptor 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Type, class ...Args> void construct(Type* pointer, Args&&... args);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Type` | 由分配器构造或销毁的对象类型。 |
| `Args` | 传递给构造函数或可调用对象的实参类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输出 | 满足目标对象大小与对齐的未初始化存储地址；调用在该处开始对象生命周期，构造实参决定其初值。 |
| `args` | 输入/输出 | 转发给对象构造或函数调用的实参列表。 |

## 返回值说明

无返回值。

## 约束说明

- 遵循scoped_allocator_adaptor的标准分配器传播、构造、销毁、比较和交换约束。
- 参与操作的分配器必须在当前可用位置有效，Device侧操作不得抛出异常。

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
    using pointer = T*;
    using size_type = ::std::size_t;
    using difference_type = ::std::ptrdiff_t;
    template <class U> struct rebind { using other = example_allocator<U>; };
    example_allocator() = default;
    template <class U> example_allocator(const example_allocator<U>&) noexcept {}
};

void example(asc::std::scoped_allocator_adaptor<example_allocator<int>>& allocator)
{
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 7);
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
