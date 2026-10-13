# asc::std::linalg::conjugated_accessor::access

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

`asc::std::linalg::conjugated_accessor::access`读取指定索引处的元素，并按值返回共轭运算结果，不修改原元素。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

所属类型：[`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)。

```cpp
// asc::std::linalg::conjugated_accessor 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr reference access(data_handle_type pointer, size_t index) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 底层数据句柄，指向待访问元素的存储。 |
| `index` | 输入 | 待访问元素相对句柄起点的元素索引。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `reference` | 按值返回共轭结果；`reference`是结果类型的别名，不表示必然返回C++ 引用。 |

## 约束说明

- 数据句柄须能经嵌套访问器访问该索引；底层存储在调用期间保持有效。
- 元素类型和共轭操作须满足嵌套访问器及共轭函数的要求。

## 调用示例

以下Host示例验证共轭结果及原数据不变。

```cpp
#include <asc/std/linalg>

bool example()
{
    asc::std::complex<float> values[1] = {{2.0F, 3.0F}};
    using accessor_type = asc::std::linalg::conjugated_accessor<asc::std::default_accessor<asc::std::complex<float>>>;
    accessor_type accessor{};
    const auto result = accessor.access(values, 0);
    return result.real() == 2.0F && result.imag() == -3.0F && values[0].imag() == 3.0F;
}
```

## 关联API

- [`asc::std::linalg::conjugated_accessor`](linalg_conjugated_accessor.md)
- [本头文件的接口列表](asc_std_linalg.md)
