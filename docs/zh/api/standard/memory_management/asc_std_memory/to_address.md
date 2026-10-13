# asc::std::to_address

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

`asc::std::to_address`把原始或自定义指针转换为底层原始地址。

标准语义参考：[cppreference `memory`](https://en.cppreference.com/w/cpp/header/memory)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Pointer> constexpr auto to_address(const Pointer& pointer) noexcept -> decltype(::asc::std::__to_address(pointer));
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> constexpr T* to_address(T* pointer) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Pointer` | 待取得底层原始地址的指针或类指针类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 提供“把原始或自定义指针转换为底层原始地址”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 被构造、销毁或管理的对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 待取得原始对象地址的指针或类指针对象；不解引用指向的对象，也不转移其所有权。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回与输入指针或指针类对象对应的原始地址。 |
| 原型2 | `T*` | 返回与输入指针或指针类对象对应的原始地址。 |

## 约束说明

- 支持原始指针和用户自定义fancy pointer，接口自身不分配内存。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/std/memory>

template <class Pointer>
decltype(auto) example(const Pointer & pointer)
{
    return asc::std::to_address(pointer);
}
```

对应完整工程使用`C++17`，并通过Host编译与运行验证。

完整示例源码：[pointer_alignment.cpp](../../../../examples/pointer_alignment.cpp)。

## 关联API

- [本头文件的接口列表](asc_std_memory.md)
