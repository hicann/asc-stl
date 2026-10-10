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

`asc::std::to_array` 从内建数组构造具有对应元素类型和长度的 array。

标准语义参考：[cppreference `array`](https://en.cppreference.com/w/cpp/header/array)。

## 函数原型

### 原型 1

```cpp
template<typename T, size_t Size> [[nodiscard]] constexpr array<remove_cv_t<T>, Size> asc::std::to_array(T (&&source)[Size]) noexcept(is_nothrow_move_constructible_v<T>);
```

### 原型 2

```cpp
template<typename T, size_t Size> [[nodiscard]] constexpr array<remove_cv_t<T>, Size> asc::std::to_array(T (&source)[Size]) noexcept(is_nothrow_constructible_v<T, T&>);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 容器保存或处理的元素类型。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 容器保存或处理的元素类型。 |
| `Size` | 表示元素数量、维度、位宽或索引的类型或编译期值，具体由声明确定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入/输出 | 源数据或源对象。异步操作完成前，其存储须保持有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的 `array` 对象。 |
| 原型 2 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的 `array` 对象。 |

## 约束说明

- 支持包括零在内的所有 N
- 成员函数和自由函数均不抛出异常

## 调用示例

以下片段用具体对象展示本页调用。

```cpp
#include <asc/std/array>

decltype(auto) example()
{
    int values[2] = {1, 2};
    return asc::std::to_array(values);
}
```
