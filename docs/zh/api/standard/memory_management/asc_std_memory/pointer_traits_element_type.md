# asc::std::pointer_traits::element_type

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

头文件路径为：`<asc/std/memory>`。

`asc::std::pointer_traits::element_type`标识所指向的元素类型。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

以下用公开特征查询实际类型；queried_type是示例名称，不是额外的公开成员。

元素类型：优先使用`Ptr::element_type`，否则从`SomePointer<T, Args...>`形式取首个类型实参；原始指针`T*`的元素类型为`T`。

```cpp
template<class Ptr>
using queried_type = typename asc::std::pointer_traits<Ptr>::element_type;
```

## 约束说明

- 元素类型：优先使用`Ptr::element_type`，否则从`SomePointer<T, Args...>`形式取首个类型实参；原始指针`T*`的元素类型为`T`。
- 指针类型必须可提取元素类型，并满足所查询成员的要求；类型查询不访问对象或分配存储。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>

template<class T>
struct example_pointer {
    using element_type = T;
    using difference_type = long;
    template<class U> using rebind = example_pointer<U>;
};

using traits = asc::std::pointer_traits<example_pointer<int>>;
static_assert(asc::std::is_same_v<typename traits::element_type, int>);
static_assert(asc::std::is_same_v<asc::std::pointer_traits<int*>::rebind<double>, double*>);
```

## 关联API

- [`asc::std::pointer_traits`](pointer_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
