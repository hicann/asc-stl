# asc::std::real

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

`asc::std::real`返回复数实部。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1：复数输入

```cpp
namespace asc::std {
template<class T> constexpr T real(const complex<T>& value) noexcept;
} // namespace asc::std
```

### 原型2：整数输入

```cpp
namespace asc::std {
template<class T, enable_if_t<is_integral_v<T>, int> = 0>
constexpr double real(T value) noexcept;
} // namespace asc::std
```

### 原型3：浮点数输入

```cpp
namespace asc::std {
template<class T, enable_if_t<is_floating_point_v<T>, int> = 0>
constexpr T real(T value) noexcept;
} // namespace asc::std
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数输入的成分类型，当前须为`float`；标量输入则分别为满足`is_integral_v<T>`或`is_floating_point_v<T>`的类型。 |

未命名模板参数默认值为0，用于选择相应标量重载，调用方无需显式提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待读取实部的复数或标量值；标量按虚部为0处理。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回复数实部，当前为`float`。 |
| 原型2 | `double` | 将输入转换为`double`。 |
| 原型3 | `T` | 按原浮点类型返回输入值。 |

## 约束说明

- `asc::std::complex`当前只支持`float`成分类型；这不限制标量重载的模板参数也只能为`float`。
- 标量重载分别由整型和浮点型特征约束；具体标量类型仍须由目标编译模式支持。
- 所列重载均为`constexpr`并具有`noexcept`声明，不修改输入对象。

## 调用示例

以下Host片段以具体复数值展示实部查询。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::real(value);
}

bool verify_example()
{
    return example() == 1.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
