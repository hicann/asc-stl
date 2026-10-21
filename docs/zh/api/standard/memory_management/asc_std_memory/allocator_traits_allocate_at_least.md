# asc::std::allocator_traits::allocate_at_least

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

本页保留原入口用于兼容性说明。`allocator_traits`没有`allocate_at_least`静态成员；本页不承诺标准库同名成员的可用性。

已提供的自由函数为[`asc::std::allocate_at_least`](allocate_at_least.md)，调用形式是`asc::std::allocate_at_least(allocator, count)`。

## 函数原型

当前产品不声明本页标题所示的接口。请使用下述已提供的接口。

## 参数说明

本页不声明可调用的接口参数。

## 返回值说明

本页不声明接口返回值；替代调用的结果见调用示例。

## 约束说明

- `allocator_traits`没有`allocate_at_least`静态成员；本页不承诺标准库同名成员的可用性。
- 已提供的自由函数为[`asc::std::allocate_at_least`](allocate_at_least.md)，调用形式是`asc::std::allocate_at_least(allocator, count)`。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>
#include <memory>

bool example()
{
    std::allocator<int> allocator;
    const auto result = asc::std::allocate_at_least(allocator, 2);
    const bool valid = result.ptr != nullptr && result.count >= 2;
    allocator.deallocate(result.ptr, result.count);
    return valid;
}
```

## 关联API

- [`asc::std::allocator_traits`](allocator_traits.md)
- [本头文件的接口列表](asc_std_memory.md)
