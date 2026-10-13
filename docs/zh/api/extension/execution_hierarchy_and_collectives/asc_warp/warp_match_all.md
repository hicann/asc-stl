# asc::warp_match_all

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

头文件路径为：`<asc/warp>`。

`asc::warp_match_all` 判断参与 Lane 提供的值是否全部相等。

## 函数原型

### 原型 1

```cpp
bool asc::warp_match_all(bool value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 2

```cpp
bool asc::warp_match_all(float value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 3

```cpp
bool asc::warp_match_all(int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 4

```cpp
bool asc::warp_match_all(long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 5

```cpp
bool asc::warp_match_all(unsigned int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 6

```cpp
bool asc::warp_match_all(unsigned long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

### 原型 6 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 参与匹配的输入值：participants 内全部 Lane 的该值按位相等时返回 true。 |
| `participants` | 输入 | 参与匹配的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：仅集合内的 Lane 参与比较。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 4 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 5 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 6 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 所有参与的活动线程必须以收敛控制流调用
- float 键按对象表示进行逐位匹配

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

__aicore__ decltype(auto) example(bool value, asc::lane_mask participants = asc::lane_mask::all())
{
    return asc::warp_match_all(value, participants);
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)
