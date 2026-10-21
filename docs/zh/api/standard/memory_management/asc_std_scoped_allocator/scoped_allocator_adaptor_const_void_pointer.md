# asc::std::scoped_allocator_adaptor::const_void_pointer

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：本页为兼容性说明，所述接口未提供
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

本页保留原入口用于兼容性说明。适配器自身未定义`const_void_pointer`；外层分配器若有同名公开成员，可能通过继承可见，但没有按内层分配器聚合或补缺的保证。

若要查询外层分配器的特征，请显式使用`asc::std::allocator_traits<OuterAllocator>`；其结果仅描述外层分配器。

## 声明

当前产品不声明本页标题所示的接口。请使用下述已提供的接口。

## 约束说明

- 适配器自身未定义`const_void_pointer`；外层分配器若有同名公开成员，可能通过继承可见，但没有按内层分配器聚合或补缺的保证。
- 若要查询外层分配器的特征，请显式使用`asc::std::allocator_traits<OuterAllocator>`；其结果仅描述外层分配器。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <asc/std/type_traits>
#include <memory>

using outer_traits = asc::std::allocator_traits<std::allocator<int>>;
static_assert(asc::std::is_same_v<outer_traits::const_void_pointer, const void*>);
```

## 关联API

- [`asc::std::scoped_allocator_adaptor`](scoped_allocator_adaptor.md)
- [本头文件的接口列表](asc_std_scoped_allocator.md)
