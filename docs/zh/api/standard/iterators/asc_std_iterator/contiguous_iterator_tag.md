# asc::std::contiguous_iterator_tag

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

`asc::std::contiguous_iterator_tag`标识对应迭代器能力或结束哨兵类别。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

Host C++20 使用系统标准库的 `std::contiguous_iterator_tag`。C++17 和 Device 保留派生自 `asc::std::random_access_iterator_tag` 的 ASC-STL 类型。

```cpp
namespace asc::std {
// Host C++20
using contiguous_iterator_tag = ::std::contiguous_iterator_tag;

// C++17 或 Device
struct contiguous_iterator_tag : asc::std::random_access_iterator_tag {};
} // namespace asc::std
```

## 约束说明

- 提供C++20公开迭代器概念和特征接口。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_base_of_v<asc::std::random_access_iterator_tag, asc::std::contiguous_iterator_tag>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
