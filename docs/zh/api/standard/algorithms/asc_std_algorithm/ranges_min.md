# asc::std::ranges::min

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::ranges::min`从C++17起支持两个值或输入范围，并可指定比较器和投影；两个值的调用返回所选对象的常量引用，范围调用返回最小元素的值。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
namespace asc::std::ranges {
min(left, right, compare, projection);
} // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
min(range, compare, projection);
} // namespace asc::std::ranges
```

## 参数说明

### 调用形式1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 参与比较的第一个值。 |
| `right` | 输入 | 参与比较的第二个值。 |
| `compare` | 输入 | 确定元素先后关系的比较对象。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数。 |

### 调用形式2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |
| `compare` | 输入 | 确定元素先后关系的比较对象。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数。 |

## 返回值说明

两个值的调用返回较小值的常量引用，其有效期受实参约束；范围调用按值返回最小元素。

| 调用形式 | 返回类型 |
| --- | --- |
| 两个值 | `const T&` |
| 范围 | `range_value_t<Range>` |

## 约束说明

- 范围调用要求非空范围及可复制的元素。
- 本期不提供initializer-list重载。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    return asc::std::ranges::min(values[0], values[1]) == 1 && asc::std::ranges::min(values) == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
