# asc::std::allocator_arg_t::allocator_arg_t

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

`asc::std::allocator_arg_t::allocator_arg_t`按本页所列构造形态初始化`allocator_arg_t`对象。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

### 原型1

```cpp
constexpr allocator_arg_t() noexcept;
```

### 原型2

```cpp
constexpr allocator_arg_t(allocator_arg_t&& other);
```

### 原型3

```cpp
constexpr allocator_arg_t(const allocator_arg_t& other);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- allocator_arg_t/allocator_arg。
- uses_allocator/uses_allocator_v。
- allocator_traits的C++20成员类型、rebind、allocate/deallocate、construct/destroy、max_size、select_on_container_copy_construction。
- uses_allocator_construction_args/make_obj_using_allocator/uninitialized_construct_using_allocator含pair递归构造。
- C++23 allocation_result与标准allocator_traits::allocate_at_least。
- 均限用户显式提供且在调用执行空间有效的allocator。

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
