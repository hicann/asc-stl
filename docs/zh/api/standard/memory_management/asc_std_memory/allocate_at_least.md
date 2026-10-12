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

`asc::std::allocate_at_least` 请求分配器分配至少 n 个对象的内存，返回包含指针与实际容量的 `allocation_result`，容量不小于请求值。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

```cpp
template<class Alloc> asc::std::allocation_result<typename asc::std::allocator_traits<Alloc>::pointer> asc::std::allocate_at_least(Alloc& a, size_t n)
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Alloc` | 控制接口实例化时使用的类型或编译期值，须满足约束说明。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入/输出 | 参与操作的对象引用；调用期间被引用对象须保持有效。 |
| `n` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::allocation_result<typename asc::std::allocator_traits<Alloc>::pointer>` | 返回该操作产生的值，具体含义由所选原型确定。 |

## 约束说明

- 分配器须满足分配器约定；返回容量不小于请求的对象数

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/memory>

template <class Alloc>
decltype(auto) example(Alloc& a, size_t n)
{
    return asc::std::allocate_at_least(a, n);
}
```
