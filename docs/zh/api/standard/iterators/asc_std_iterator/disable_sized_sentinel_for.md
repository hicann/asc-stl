# asc::std::disable_sized_sentinel_for

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

头文件路径为：`<asc/std/iterator>`。

`disable_sized_sentinel_for<Sentinel, Iter>`标记哨兵与迭代器的减法不应被当作有效的常量时间距离计算。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

```cpp
namespace asc::std {
template<class Sentinel, class Iter>
inline constexpr bool disable_sized_sentinel_for = false;
}
```

## 约束说明

- 提供C++20公开迭代器概念和特征接口。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    static_assert(!asc::std::disable_sized_sentinel_for<int*, int*>);
    static_assert(asc::std::sized_sentinel_for<int*, int*>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
