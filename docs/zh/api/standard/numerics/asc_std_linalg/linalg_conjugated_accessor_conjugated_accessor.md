# asc::std::linalg::conjugated_accessor::conjugated_accessor

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

头文件路径为：`<asc/std/linalg>`。

`asc::std::linalg::conjugated_accessor::conjugated_accessor`按本页所列构造形态初始化`conjugated_accessor`对象。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

### 原型1

```cpp
constexpr conjugated_accessor();
```

### 原型2

```cpp
constexpr conjugated_accessor(const NestedAccessor& accessor);
```

### 原型3

```cpp
template<class OtherNestedAccessor> constexpr conjugated_accessor(const conjugated_accessor<OtherNestedAccessor>& other);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `accessor` | 输入 | 提供“按本页所列构造形态初始化`conjugated_accessor`对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherNestedAccessor` | 来源访问器类型；须能转换为当前嵌套访问器类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 构造来源对象；本对象由其对应成员或底层状态初始化，右值形式可移动该状态。 |

## 返回值说明

无返回值。

## 约束说明

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>
#include <asc/std/type_traits>

using Accessor = asc::std::linalg::conjugated_accessor<asc::std::default_accessor<asc::std::complex<float>>>;

bool example()
{
    asc::std::complex<float> values[] = {{2.0f, 3.0f}};
    Accessor accessor;
    auto value = accessor.access(values, 0);
    return value.real() == 2.0f && value.imag() == -3.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_linalg.md)
