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

`construct`在`pointer`处直接执行以`args...`为实参的原位构造。当前不根据`uses_allocator`添加分配器参数，也不调用外层分配器的`construct`钩子。

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

- `pointer`必须是满足`Type`大小和对齐的未初始化存储，且`Type`可由转发后的`args...`构造。
- 本接口不注入内层分配器。需要分配器的构造函数，其全部参数必须由调用方显式提供。
- 对象成功构造后须销毁再释放存储；Device构造必须可调用且不抛出异常。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/scoped_allocator>
#include <memory>
#include <limits>

template<class T>
struct example_allocator {
    using value_type = T;
    using pointer = T*;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    template<class U> struct rebind { using other = example_allocator<U>; };
    int identity = 0;
    T* allocate(size_type count) { return std::allocator<T>{}.allocate(count); }
    void deallocate(T* address, size_type count) { std::allocator<T>{}.deallocate(address, count); }
    size_type max_size() const noexcept { return std::numeric_limits<size_type>::max() / sizeof(T); }
};

bool example()
{
    using adaptor = asc::std::scoped_allocator_adaptor<example_allocator<int>>;
    adaptor allocator(example_allocator<int>{7});
    int* pointer = allocator.allocate(1);
    allocator.construct(pointer, 9);
    const bool valid = allocator.outer_allocator().identity == 7 && *pointer == 9;
    allocator.destroy(pointer);
    allocator.deallocate(pointer, 1);
    return valid;
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
