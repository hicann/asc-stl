# asc::std::allocate_at_least

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

`asc::std::allocate_at_least`请求分配器分配至少n个对象的内存，返回包含指针与实际容量的`allocation_result`，容量不小于请求值。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
namespace asc::std {
template<class Alloc> [[nodiscard]] constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least(Alloc& __alloc, size_t __n);
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 用于本次分配的分配器类型；须满足allocator_traits的分配与数量约定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `__alloc` | 输入/输出 | 分配器对象；调用期间须保持有效，其分配结果按该分配器的释放规则管理。 |
| `__n` | 输入 | 请求的元素数量，单位为对象个数；须在分配器可处理的范围内。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::allocation_result<typename asc::std::allocator_traits<Alloc>::pointer>` | 返回分配地址ptr和实际可容纳的元素数量count；count不小于请求数量。 |

## 约束说明

- C++17和C++20均优先调用可用的`allocate_at_least`成员，并保留其返回的实际容量；没有匹配成员时调用`allocate`并返回请求数量作为容量。
- 分配器须满足分配与释放约定，成员返回的容量不得小于请求数量。调用方负责按分配器要求释放所得存储。
- 是否能够在Device执行、是否分配设备内存以及错误行为，由具体分配器决定。此模板不提供隐式的设备动态分配。
- `constexpr`不保证任意分配器都能在常量求值期间分配存储。

## 调用示例

示例分配器使用调用方预留的存储。成员额外提供一个元素的容量，结果由指针和容量共同检查。

```cpp
#include <asc/std/memory>

struct example_allocator {
    using value_type = int;
    int* storage;
    int* allocate(asc::std::size_t) { return storage; }
    asc::std::allocation_result<int*> allocate_at_least(asc::std::size_t count)
    {
        return {storage, count + 1};
    }
    void deallocate(int*, asc::std::size_t) noexcept {}
};

bool example()
{
    int storage[4] = {};
    example_allocator allocator{storage};
    const auto result = asc::std::allocate_at_least(allocator, 2);
    const bool valid = result.ptr == storage && result.count == 3;
    allocator.deallocate(result.ptr, result.count);
    return valid;
}
```

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
