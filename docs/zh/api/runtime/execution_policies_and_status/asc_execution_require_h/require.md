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

`asc::require` 创建执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。

该接口的可用位置为 Host。

## 函数原型

### 原型 1

```cpp
constexpr asc::execution_requirements asc::require(asc::determinism value) noexcept;
```

### 原型 2

```cpp
constexpr asc::execution_requirements asc::require(asc::execution_requirements base, asc::determinism value) noexcept;
```

### 原型 3

```cpp
constexpr asc::execution_requirements asc::require(asc::execution_requirements base, asc::output_ordering value) noexcept;
```

### 原型 4

```cpp
constexpr asc::execution_requirements asc::require(asc::execution_requirements base, asc::tie_break value) noexcept;
```

### 原型 5

```cpp
constexpr asc::execution_requirements asc::require(asc::output_ordering value) noexcept;
```

### 原型 6

```cpp
constexpr asc::execution_requirements asc::require(asc::tie_break value) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 提供“创建执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度”所需的输入对象；类型须满足所选原型约束。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 提供“创建执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度”所需的输入对象；类型须满足所选原型约束。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 提供“创建执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度”所需的输入对象；类型须满足所选原型约束。 |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

### 原型 6 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型 2 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型 3 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型 4 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型 5 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |
| 原型 6 | `asc::execution_requirements` | 返回执行要求组合，或在现有组合中替换确定性、输出顺序或相同键值处理规则中的一个维度，并保留其余维度。 |

## 约束说明

- sets determinism on default 要求ments
- 仅替换函数名称所指明的执行要求、Stream 或临时存储绑定，其余策略属性保持不变
- sets output ordering on default 要求ments
- sets tie break on default 要求ments

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/execution.require.h>

decltype(auto) example(asc::determinism value)
{
    return asc::require(value);
}
```
