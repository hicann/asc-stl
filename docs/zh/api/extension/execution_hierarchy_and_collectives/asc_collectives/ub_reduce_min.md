# asc::ub_reduce_min

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

头文件路径为：`<asc/collectives>`。

`asc::ub_reduce_min`返回UB连续范围中的最小元素值。

## 函数原型

### 原型1

```cpp
namespace asc {
asc::std::int32_t ub_reduce_min(asc::ub_span<const asc::std::int32_t> input) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
asc::std::uint32_t ub_reduce_min(asc::ub_span<const asc::std::uint32_t> input) noexcept;
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
float ub_reduce_min(asc::ub_span<const float> input) noexcept;
}  // namespace asc
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 观察片上缓冲区连续区域的非拥有视图；底层存储须在操作期间有效。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 观察片上缓冲区连续区域的非拥有视图；底层存储须在操作期间有效。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `input` | 输入 | 观察片上缓冲区连续区域的非拥有视图；底层存储须在操作期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::std::int32_t` | 返回参与线程或连续范围按接口名称归约后的结果。 |
| 原型2 | `asc::std::uint32_t` | 返回参与线程或连续范围按接口名称归约后的结果。 |
| 原型3 | `float` | 返回参与线程或连续范围按接口名称归约后的结果。 |

## 约束说明

- 输入/输出为调用方管理的UB范围；有符号求和或扫描的所有中间值和最终值须可表示。 min/max要求非空输入；空输入的防御返回零不代表空集合存在极值。

- 仅可在AI Core SIMD编程中调用。
- 参数类型、地址空间、取值范围和对象生命周期必须满足页面声明。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(__ubuf__ const unsigned int* input)
{
    // 输入指向当前线程块 UB 中至少四个有效元素。
    return asc::ub_reduce_min(asc::ub_span<const unsigned int>(input, 4u));
}
```

## 关联API

- [本头文件的接口列表](asc_collectives.md)
