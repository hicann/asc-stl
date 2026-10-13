# asc::std::data

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

`asc::std::data`取得连续范围的首元素地址。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Cont> [[nodiscard]] constexpr auto data(Cont& container) noexcept(noexcept(C.data())) -> decltype(C.data());
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class Cont> [[nodiscard]] constexpr auto data(const Cont& container) noexcept(noexcept(C.data())) -> decltype(C.data());
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<class T, size_t Sz> constexpr T* data(T (&container)[Sz]) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Cont` | 被查询容器的类型；须提供本重载调用的size、empty或data成员。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Cont` | 被查询容器的类型；须提供本重载调用的size、empty或data成员。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 内建数组的元素类型。 |
| `Sz` | 内建数组在该维度的元素数量，由数组实参推导。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `decltype(C.data())` | 返回连续范围的首元素地址。 |
| 原型2 | `decltype(C.data())` | 返回连续范围的首元素地址。 |
| 原型3 | `T *` | 返回连续范围的首元素地址。 |

## 约束说明

- 支持非I/O范围、数组和用户容器。

## 调用示例

以下Host片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::data(values);
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
