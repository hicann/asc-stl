# asc::std::to_array

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

头文件路径为：`<asc/std/array>`。

`asc::std::to_array`从内建数组构造具有对应元素类型和长度的array。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<typename T, size_t Size> constexpr array<remove_cv_t<T>, Size> to_array(T (&&source)[Size]) noexcept(is_nothrow_move_constructible_v<T>);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<typename T, size_t Size> constexpr array<remove_cv_t<T>, Size> to_array(T (&source)[Size]) noexcept(is_nothrow_constructible_v<T, T&>);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 源内建数组的元素类型；结果元素类型为`remove_cv_t<T>`。 |
| `Size` | 输入内建数组的元素数量，由数组类型推导；结果`asc::std::array`具有相同的元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入/输出 | 右值内建数组；逐元素移动构造返回的`array`，源元素的后续状态由`T`的移动构造语义决定。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 源内建数组的元素类型；结果元素类型为`remove_cv_t<T>`。 |
| `Size` | 输入内建数组的元素数量，由数组类型推导；结果`asc::std::array`具有相同的元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 左值内建数组；从各源元素构造返回的`array`元素。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的`array`对象。 |
| 原型2 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的`array`对象。 |

## 约束说明

- 左值和右值数组重载均从C++17起提供。
- `Size`由源内建数组的长度推导。标准C++的内建数组长度须大于0；不接受多维数组，即`T`不能仍为数组类型。
- 原型1要求`is_move_constructible_v<T>`为`true`；原型2要求`is_constructible_v<T, T&>`为`true`。不要求元素可默认构造。
- 原型1仅在`is_nothrow_move_constructible_v<T>`为`true`时为`noexcept`；原型2仅在`is_nothrow_constructible_v<T, T&>`为`true`时为`noexcept`。Device侧使用的元素构造须不抛出异常。
- 返回的`array`具有独立的元素存储；元素自身持有的指针、引用或其他资源的有效期仍由`T`的语义决定。

## 调用示例

以下Host示例使用具体对象，并检查调用结果。

```cpp
#include <asc/std/array>

bool example()
{
    int source[2] = {2, 4};
    const auto result = asc::std::to_array(source);
    source[0] = 9;
    return result.size() == 2 && result[0] == 2 && result[1] == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_array.md)
