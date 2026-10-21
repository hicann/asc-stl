# asc::std::linalg::scaled_accessor::offset

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

`asc::std::linalg::scaled_accessor::offset`按映射结果移动底层数据句柄。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

所属类型：[`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)。

```cpp
// asc::std::linalg::scaled_accessor 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr typename offset_policy::data_handle_type offset(data_handle_type pointer, size_t index) const;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `pointer` | 输入 | 待移动的底层数据句柄。 |
| `index` | 输入 | 句柄向前移动的元素个数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `typename offset_policy::data_handle_type` | 返回经嵌套访问器前移index个元素后的数据句柄；默认访问器返回同一底层数组内的指针，存储须在使用句柄时保持有效。 |

## 约束说明

- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并在对象与底层存储仍有效时检查结果。

```cpp
#include <asc/std/linalg>

bool example()
{
    float values[2]{};
    using A = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;
    A accessor{};
    const auto pointer = accessor.offset(values, 1);
    return pointer == values + 1;
}
```

## 关联API

- [`asc::std::linalg::scaled_accessor`](linalg_scaled_accessor.md)
- [本头文件的接口列表](asc_std_linalg.md)
