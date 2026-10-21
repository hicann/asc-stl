# asc::require

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

头文件路径为：`<asc/execution.require.h>`。

`asc::require`创建执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。

该接口的可用位置为Host。

## 函数原型

### 原型1

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::determinism value) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::determinism value) noexcept;
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::output_ordering value) noexcept;
}  // namespace asc
```

### 原型4

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::execution_requirements base, asc::tie_break value) noexcept;
}  // namespace asc
```

### 原型5

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::output_ordering value) noexcept;
}  // namespace asc
```

### 原型6

```cpp
namespace asc {
constexpr asc::execution_requirements require(asc::tie_break value) noexcept;
}  // namespace asc
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 确定性要求枚举值（asc::determinism：device_to_device、run_to_run、not_guaranteed）：在默认组合基础上设置该维度。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 现有执行要求组合：返回的组合仅替换其中的确定性维度，其余维度保留原值。 |
| `value` | 输入 | 确定性要求枚举值（asc::determinism）：替换base组合中的确定性维度。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 现有执行要求组合：返回的组合仅替换其中的输出顺序维度，其余维度保留原值。 |
| `value` | 输入 | 输出顺序要求枚举值（asc::output_ordering）：替换base组合中的输出顺序维度。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 现有执行要求组合：返回的组合仅替换其中的相同键值处理维度，其余维度保留原值。 |
| `value` | 输入 | 相同键值处理规则枚举值（asc::tie_break）：替换base组合中的该维度。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 输出顺序要求枚举值（asc::output_ordering：sorted、stable_sorted、unsorted）：在默认组合基础上设置该维度。 |

### 原型6的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 相同键值处理规则枚举值（asc::tie_break：unspecified、prefer_smaller_index、prefer_larger_index）：在默认组合基础上设置该维度。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型2 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型3 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型4 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型5 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型6 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |

## 约束说明

- Host同步构造或更新执行要求值，不提交任务。
- 带`base`的重载仅替换本次传入的确定性、输出顺序或索引偏好，保留其他两项。
- 不带`base`的重载从默认执行要求构造；不绑定或改变Stream和临时存储。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/execution.require.h>

decltype(auto) example(asc::determinism value)
{
    return asc::require(value);
}
```

## 关联API

- [本头文件的接口列表](asc_execution_require_h.md)
