# asc::std::allocator_arg_t

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

`asc::std::allocator_arg_t`标记对象构造时显式传入分配器。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 声明

```cpp
namespace asc::std {
struct allocator_arg_t;
} // namespace asc::std
```

## 约束说明

- 这是标识显式分配器构造形式的空标签，不保存分配器、不申请存储，也不自动选择构造函数。

## 调用示例

带分配器的用户类型可将allocator_arg_t放在构造函数首参，明确区分分配器与普通实参。

```cpp
#include <asc/std/memory>
#include <memory>

struct Value {
    using allocator_type = ::std::allocator<int>;
    int number;
    Value(asc::std::allocator_arg_t, const allocator_type&, int input) : number(input) {}
};

bool example()
{
    static_assert(asc::std::uses_allocator_v<Value, ::std::allocator<int>>);
    asc::std::allocator_arg_t tag{};
    Value value(tag, ::std::allocator<int>{}, 7);
    return value.number == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
