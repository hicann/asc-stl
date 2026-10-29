# asc::std::scoped_allocator_adaptor::destroy

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

`asc::std::scoped_allocator_adaptor::destroy`结束已构造对象的生命周期。

标准语义参考：[cppreference `scoped_allocator`](https://en.cppreference.com/w/cpp/header/scoped_allocator)。

## 函数原型

所属类型：[`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)。

```cpp
// asc::std::scoped_allocator_adaptor 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Type> void destroy(Type* pointer);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Type` | 由分配器构造或销毁的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入/输出 | 指向生命周期尚未结束的对象；调用结束其生命周期，不释放底层存储。 |

## 返回值说明

无返回值。

## 约束说明

- 直接结束`pointer`处单个存活对象的生命周期，不释放存储，也不调用外层分配器的销毁钩子。
- 指针须指向仍存活的对象；Device析构必须可调用且不抛出异常。

## 调用示例

以下Host片段使用显式提供的分配器并完整释放存储；设备端须改用目标位置可调用的分配器。

```cpp
#include <asc/std/scoped_allocator>
#include <asc/std/type_traits>
#include <memory>

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

struct example_value {
    static inline int alive = 0;
    int value;
    explicit example_value(int input) : value(input) { ++alive; }
    ~example_value() { --alive; }
};

bool verify_example()
{
    asc::std::scoped_allocator_adaptor<example_allocator<example_value>> allocator;
    example_value* pointer = allocator.allocate(1);
    allocator.construct(pointer, 7);
    const bool constructed = example_value::alive == 1 && pointer->value == 7;
    allocator.destroy(pointer);
    const bool destroyed = example_value::alive == 0;
    allocator.deallocate(pointer, 1);
    return constructed && destroyed;
}
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
