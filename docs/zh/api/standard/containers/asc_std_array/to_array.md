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
| `T` | 容器保存或处理的元素类型。 |
| `Size` | 输入内建数组的元素数量，由数组类型推导；结果`asc::std::array`具有相同的元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入/输出 | 源内建数组。返回的`array`对象拥有各元素的副本（左值源）或被移动的元素（右值源），不引用源数据；调用返回后源数组即可释放或复用。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 容器保存或处理的元素类型。 |
| `Size` | 输入内建数组的元素数量，由数组类型推导；结果`asc::std::array`具有相同的元素数量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入/输出 | 源内建数组。返回的`array`对象拥有各元素的副本（左值源）或被移动的元素（右值源），不引用源数据；调用返回后源数组即可释放或复用。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的`array`对象。 |
| 原型2 | `array<remove_cv_t<T>, Size>` | 返回元素类型由输入数组推导、长度保持不变的`array`对象。 |

## 约束说明

- 左值和右值数组重载均从C++17起提供，元素数量由一维内建数组类型确定。
- 左值重载要求元素可从对应左值构造；右值重载要求元素可移动构造。元素无需可默认构造。
- 不接受多维内建数组。异常约定由相应元素构造和声明中的`noexcept`条件决定；Device调用的元素构造须满足设备异常限制。

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
