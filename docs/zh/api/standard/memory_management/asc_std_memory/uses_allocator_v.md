# asc::std::uses_allocator_v

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

`asc::std::uses_allocator_v`在编译期判断类型是否使用给定分配器。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

```cpp
namespace asc::std {
template<class T, class Alloc>
inline constexpr bool uses_allocator_v = uses_allocator<T, Alloc>::value;
}
```

## 约束说明

- 普通类型在有`allocator_type`且`Alloc`可转换为该类型时为`true`，否则为`false`；`tuple`使用其公开特化规则。
- 读取该变量模板不构造对象、不传递分配器，也不保证具体构造函数能调用。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/memory>

struct example_allocator {};
struct allocated_value { using allocator_type = example_allocator; };
static_assert(asc::std::uses_allocator_v<allocated_value, example_allocator>);
static_assert(!asc::std::uses_allocator_v<int, example_allocator>);
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
