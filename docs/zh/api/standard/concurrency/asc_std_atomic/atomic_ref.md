# asc::std::atomic_ref

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

头文件路径为：`<asc/std/atomic>`。

`asc::std::atomic_ref`以非拥有方式对已有对象执行原子操作。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 声明

```cpp
namespace asc::std {
template<class T> class atomic_ref;
} // namespace asc::std
```

## 约束说明

- 原子对象的类型、地址空间、作用域和内存序必须匹配。
- Device作用域的64位对象位于GM，UB原子操作仅使用memory_order_relaxed。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/atomic>

bool example()
{
    int value = 1;
    asc::std::atomic_ref<int> reference(value);
    reference.store(4);
    return value == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_atomic.md)
