# asc::std::align_val_t

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

头文件路径为：`<asc/std/new>`。

`asc::std::align_val_t`把扩展对齐值传给定位对象生命周期接口。

标准语义参考：[cppreference `new`](https://en.cppreference.com/w/cpp/header/new)。

## 声明

底层类型是编译器给出的size_t类型；这是ASC-STL自身的作用域枚举。

```cpp
namespace asc::std {
enum class align_val_t : __SIZE_TYPE__ {};
}
```

## 约束说明

- 提供placement对象生命周期和无动态分配的接口。

## 调用示例

该枚举携带对齐字节数，值应为2的幂。它与系统std::align_val_t是不同类型，不能直接传给系统的对齐new重载。

```cpp
#include <asc/std/new>
#include <asc/std/cstddef>

bool example()
{
    constexpr asc::std::align_val_t alignment{64};
    static_assert(static_cast<asc::std::size_t>(alignment) == 64);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_new.md)
