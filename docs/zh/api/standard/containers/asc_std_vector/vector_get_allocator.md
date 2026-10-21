# asc::std::vector::get_allocator

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

头文件路径为：`<asc/std/vector>`。

`asc::std::vector::get_allocator`返回容器当前使用的分配器。

标准语义参考：[cppreference `vector`](https://en.cppreference.com/w/cpp/header/vector)。

## 函数原型

所属类型：[`asc::std::vector`](vector.md)。

```cpp
// asc::std::vector 类内的声明节选；模板形参和其他成员由所属类提供。
allocator_type get_allocator() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `allocator_type` | 返回容器当前使用的分配器。 |

## 约束说明

- 返回所保存分配器的副本，不分配元素存储；分配器复制操作须不抛出异常。
- 在Device侧调用时，分配器复制操作须可用于相应编程模式。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <memory>
#include <asc/std/vector>

bool example()
{
    asc::std::vector<int, ::std::allocator<int>> values(::std::allocator<int>{});
    values.push_back(1);
    values.push_back(3);

    auto allocator = values.get_allocator();
    auto* buffer = allocator.allocate(1);
    if (buffer == nullptr) return false;
    ::std::allocator_traits<decltype(allocator)>::construct(allocator, buffer, 7);
    const bool matched = *buffer == 7;
    ::std::allocator_traits<decltype(allocator)>::destroy(allocator, buffer);
    allocator.deallocate(buffer, 1);
    return matched;
}
```

## 关联API

- [`asc::std::vector`](vector.md)
- [本头文件的接口列表](asc_std_vector.md)
