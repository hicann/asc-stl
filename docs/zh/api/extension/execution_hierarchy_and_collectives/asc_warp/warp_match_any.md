# asc::warp_match_any

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

`asc::warp_match_any` 返回与当前 Lane 值相等的参与 Lane 掩码。

## 函数原型

### 原型 1

```cpp
asc::lane_mask asc::warp_match_any(bool value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 2

```cpp
asc::lane_mask asc::warp_match_any(float value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 3

```cpp
asc::lane_mask asc::warp_match_any(int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 4

```cpp
asc::lane_mask asc::warp_match_any(long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 5

```cpp
asc::lane_mask asc::warp_match_any(unsigned int value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 6

```cpp
asc::lane_mask asc::warp_match_any(unsigned long long value, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

### 原型 6 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `participants` | 输入 | 指定参与线程束操作的活动 Lane 集合。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |
| 原型 2 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |
| 原型 3 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |
| 原型 4 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |
| 原型 5 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |
| 原型 6 | `asc::lane_mask` | 返回与当前 Lane 值相等的参与 Lane 掩码。 |

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
    return asc::warp_match_any(value, participants);
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)
