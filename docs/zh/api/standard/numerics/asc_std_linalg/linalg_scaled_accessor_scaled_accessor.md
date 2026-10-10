# asc::std::linalg::scaled_accessor::scaled_accessor

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

`asc::std::linalg::scaled_accessor::scaled_accessor` 按本页所列构造形态初始化 `scaled_accessor` 对象。

标准语义参考：[cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg)。

## 函数原型

### 原型 1

```cpp
constexpr scaled_accessor();
```

### 原型 2

```cpp
constexpr scaled_accessor(const ScalingFactor& scale, const NestedAccessor& accessor);
```

### 原型 3

```cpp
template<class OtherScalingFactor, class OtherNestedAccessor> constexpr scaled_accessor(const scaled_accessor<OtherScalingFactor, OtherNestedAccessor>& other);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `scale` | 输入 | 提供“按本页所列构造形态初始化 `scaled_accessor` 对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `accessor` | 输入 | 提供“按本页所列构造形态初始化 `scaled_accessor` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `OtherScalingFactor` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `OtherNestedAccessor` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 约束说明

- 固定当前版本的 C++ 标准库公共入口的完整7实体合同：scaled/scaled_accessor、conjugated/conjugated_accessor、transposed/layout_transpose、conjugate_transposed
- 包括access/offset/nested accessor/factor、转换构造、算术类型共轭不变、ADL可共轭类型、双重共轭/转置消去、rank-2静态/动态extents交换、layout_left/right/stride与通用layout_transpose mapping全部观察/比较
- 对所依赖mdspan/accessor/缩放与共轭运算已交付的有效实例为Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段使用具体范围或访问器演示调用；底层存储在调用期间须保持有效。

```cpp
#include <asc/std/linalg>

void example()
{
    using accessor_type = asc::std::linalg::scaled_accessor<float, asc::std::default_accessor<float>>;
    accessor_type accessor{};
    (void)accessor;
}
```
