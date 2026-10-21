# asc::std::get_if

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

头文件路径为：`<asc/std/variant>`。

`asc::std::get_if`活动备选项与目标匹配时返回其指针，否则返回空指针。

标准语义参考：[cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T, class ...Types> [[nodiscard]] constexpr add_pointer_t<T> get_if(variant<Types...>* value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T, class ...Types> [[nodiscard]] constexpr add_pointer_t<const T> get_if(const variant<Types...>* value) noexcept;
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<size_t Index, class ...Types> [[nodiscard]] constexpr add_pointer_t<const variant_alternative_t<Index, variant<Types...>>> get_if(const variant<Types...>* value) noexcept;
} // namespace asc::std
```

### 原型4

```cpp
namespace asc::std {
template<size_t Index, class ...Types> [[nodiscard]] constexpr add_pointer_t<variant_alternative_t<Index, variant<Types...>>> get_if(variant<Types...>* value) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 目标备选项类型；须在Types... 中恰好出现一次。 |
| `Types` | variant的备选项类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被访问的variant对象指针；活动备选项与目标匹配时返回其备选项指针，否则返回空指针。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 目标备选项类型；须在Types... 中恰好出现一次。 |
| `Types` | variant的备选项类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被访问的variant对象指针；活动备选项与目标匹配时返回其备选项指针，否则返回空指针。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标备选项的下标（从0起）；须小于备选项数量。 |
| `Types` | variant的备选项类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被访问的variant对象指针；活动备选项与目标匹配时返回其备选项指针，否则返回空指针。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Index` | 目标备选项的下标（从0起）；须小于备选项数量。 |
| `Types` | variant的备选项类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 被访问的variant对象指针；活动备选项与目标匹配时返回其备选项指针，否则返回空指针。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `add_pointer_t<T>` | 返回其指针，否则返回空指针。 |
| 原型2 | `add_pointer_t<const T>` | 返回其指针，否则返回空指针。 |
| 原型3 | `add_pointer_t<const variant_alternative_t<Index, variant<Types...>>>` | 返回其指针，否则返回空指针。 |
| 原型4 | `add_pointer_t<variant_alternative_t<Index, variant<Types...>>>` | 返回其指针，否则返回空指针。 |

## 约束说明

- 对象没有活动备选项时返回空指针；可据此避免访问不存在的值。

- Device侧备选类型以及所选构造、赋值和交换操作必须不抛出异常。
- 返回的引用、指针或非拥有包装器不延长被引用对象的生命周期。使用时须保证该对象仍存活；对象销毁或其值存储生命周期结束后不得继续访问。

## 调用示例

以下Host示例在被引用对象仍存活时检查结果。

```cpp
#include <asc/std/variant>

bool example()
{
    asc::std::variant<int, long> value(asc::std::in_place_index<0>, 7);
    int* selected = asc::std::get_if<0>(&value);
    return selected != nullptr && *selected == 7 && asc::std::get_if<1>(&value) == nullptr;
}
```

## 关联API

- [本头文件的接口列表](asc_std_variant.md)
