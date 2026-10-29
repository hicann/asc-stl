# asc::std::norm

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

头文件路径为：`<asc/std/complex>`。

`asc::std::norm`返回复数模的平方。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T> constexpr T norm(const complex<T>& value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr T norm(T value) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数操作数的成分类型，当前须为`float`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求模平方（实部平方加虚部平方）的复数操作数。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 实数输入的值类型，返回值为该值的平方。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求模平方的实数输入（返回value * value）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回复数模的平方。 |
| 原型2 | `T` | 返回复数模的平方。 |

## 约束说明

- 复数重载当前仅接受`complex<float>`；标量重载直接计算`value * value`并按`T`返回，不构造复数。
- 标量类型须支持该乘法表达式及结果到`T`的转换，并满足目标编译模式的类型能力。
- 两个重载均具有`noexcept`声明。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::norm(value);
}

bool verify_example()
{
    return example() == 5.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
