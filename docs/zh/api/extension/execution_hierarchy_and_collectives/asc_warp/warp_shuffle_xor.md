# asc::warp_shuffle_xor

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

`asc::warp_shuffle_xor` 读取 Lane 编号与 xor_mask 异或后对应 Lane 的值。

## 函数原型

### 原型 1

```cpp
template<int Width = 32> asc::warp_shuffle_result<float> asc::warp_shuffle_xor(float value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 2

```cpp
template<int Width = 32> asc::warp_shuffle_result<int> asc::warp_shuffle_xor(int value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 3

```cpp
template<int Width = 32> asc::warp_shuffle_result<long long> asc::warp_shuffle_xor(long long value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 4

```cpp
template<int Width = 32> asc::warp_shuffle_result<unsigned int> asc::warp_shuffle_xor(unsigned int value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

### 原型 5

```cpp
template<int Width = 32> asc::warp_shuffle_result<unsigned long long> asc::warp_shuffle_xor(unsigned long long value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取 1/2/4/8/16/32，默认 32）：Lane 按 Width 分组，目标 Lane 须与调用 Lane 同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 提供参与洗牌的值：返回值来自同一分组内编号为 本 Lane 编号 xor xor_mask 的 Lane。 |
| `xor_mask` | 输入 | 与本 Lane 编号（0 起）按位异或得到目标 Lane 编号的掩码。 |
| `participants` | 输入 | 参与本操作的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取 1/2/4/8/16/32，默认 32）：Lane 按 Width 分组，目标 Lane 须与调用 Lane 同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 提供参与洗牌的值：返回值来自同一分组内编号为 本 Lane 编号 xor xor_mask 的 Lane。 |
| `xor_mask` | 输入 | 与本 Lane 编号（0 起）按位异或得到目标 Lane 编号的掩码。 |
| `participants` | 输入 | 参与本操作的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取 1/2/4/8/16/32，默认 32）：Lane 按 Width 分组，目标 Lane 须与调用 Lane 同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 提供参与洗牌的值：返回值来自同一分组内编号为 本 Lane 编号 xor xor_mask 的 Lane。 |
| `xor_mask` | 输入 | 与本 Lane 编号（0 起）按位异或得到目标 Lane 编号的掩码。 |
| `participants` | 输入 | 参与本操作的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取 1/2/4/8/16/32，默认 32）：Lane 按 Width 分组，目标 Lane 须与调用 Lane 同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 提供参与洗牌的值：返回值来自同一分组内编号为 本 Lane 编号 xor xor_mask 的 Lane。 |
| `xor_mask` | 输入 | 与本 Lane 编号（0 起）按位异或得到目标 Lane 编号的掩码。 |
| `participants` | 输入 | 参与本操作的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取 1/2/4/8/16/32，默认 32）：Lane 按 Width 分组，目标 Lane 须与调用 Lane 同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本 Lane 提供参与洗牌的值：返回值来自同一分组内编号为 本 Lane 编号 xor xor_mask 的 Lane。 |
| `xor_mask` | 输入 | 与本 Lane 编号（0 起）按位异或得到目标 Lane 编号的掩码。 |
| `participants` | 输入 | 参与本操作的 Lane 集合掩码（lane_mask，bit i 对应 Lane i，默认 lane_mask::all()）：自身或目标不在集合内时结果无效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::warp_shuffle_result<float>` | 返回按指定线程束来源位置取得的值。 |
| 原型 2 | `asc::warp_shuffle_result<int>` | 返回按指定线程束来源位置取得的值。 |
| 原型 3 | `asc::warp_shuffle_result<long long>` | 返回按指定线程束来源位置取得的值。 |
| 原型 4 | `asc::warp_shuffle_result<unsigned int>` | 返回按指定线程束来源位置取得的值。 |
| 原型 5 | `asc::warp_shuffle_result<unsigned long long>` | 返回按指定线程束来源位置取得的值。 |

## 约束说明

- 仅可在 AI Core SIMT 编程中调用
- 所有参与的活动线程必须以收敛控制流调用
- Width 只能取 1、2、4、8、16 或 32

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

template <int Width>
__aicore__ decltype(auto) example(float value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all())
{
    return asc::warp_shuffle_xor<Width>(value, xor_mask, participants);
}
```

对应完整工程使用 `C++17`，并通过Ascend 950 真机编译与运行验证。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)
