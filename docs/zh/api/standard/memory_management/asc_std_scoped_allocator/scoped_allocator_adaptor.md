# asc::std::scoped_allocator_adaptor

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

`asc::std::scoped_allocator_adaptor`保存外层及可选内层分配器，并将存储申请和释放交给外层分配器。当前`construct`直接以传入实参构造对象，不执行标准uses-allocator递归参数注入。

## 声明

先列主模板，再列无内层和有内层分配器的两个偏特化。

```cpp
namespace asc::std {
template<class OuterAllocator, class... InnerAllocators>
class scoped_allocator_adaptor;

template<class OuterAllocator>
class scoped_allocator_adaptor<OuterAllocator>;

template<class OuterAllocator, class FirstInner, class... RestInner>
class scoped_allocator_adaptor<OuterAllocator, FirstInner, RestInner...>;
}
```

## 约束说明

- `OuterAllocator`须自带`value_type`、`pointer`、`size_type`、`difference_type`及重绑定所需成员；本类不会用`allocator_traits`为这些名字补缺。
- `allocate`、`deallocate`和`max_size`直接使用外层分配器的对应操作。内层分配器可通过`inner_allocator()`查询。
- `construct`只转发调用者给出的实参；不自动传入`allocator_arg`、内层分配器或递归处理pair。
- 不提供标准完整的传播特征、递归复制选择和提示分配重载。继承自外层分配器的同名成员只具有该外层类型自身的语义。
- Device使用要求分配器及元素操作在对应执行位置有效且不抛出异常。

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

- [本头文件的接口列表](asc_std_scoped_allocator.md)
