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

`asc::std::data` 取得连续范围的首元素地址。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 函数原型

### 原型 1

```cpp
template<class Cont> [[nodiscard]] constexpr auto asc::std::data(Cont& container) noexcept(noexcept(C.data())) -> decltype(C.data());
```

### 原型 2

```cpp
template<class Cont> [[nodiscard]] constexpr auto asc::std::data(const Cont& container) noexcept(noexcept(C.data())) -> decltype(C.data());
```

### 原型 3

```cpp
template<class T, size_t Sz> constexpr T* asc::std::data(T (&container)[Sz]) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Cont` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Cont` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `Sz` | 所选原型使用的编译期值；允许范围由声明和约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `container` | 输入/输出 | 提供“取得连续范围的首元素地址”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `decltype(C.data())` | 返回连续范围的首元素地址。 |
| 原型 2 | `decltype(C.data())` | 返回连续范围的首元素地址。 |
| 原型 3 | `T *` | 返回连续范围的首元素地址。 |

## 约束说明

- 支持非 I/O 范围、数组和用户容器

## 调用示例

以下 Host 片段使用具体数组或显式容器演示调用；迭代器须保持在有效范围内。

```cpp
#include <asc/std/iterator>

decltype(auto) example()
{
    int values[4] = {1, 2, 3, 4};
    return asc::std::data(values);
}
```
