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

`asc::warp_shuffle_xor`读取Lane编号与xor_mask异或后对应Lane的值。

## 函数原型

### 原型1

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<float> warp_shuffle_xor(
    float value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### 原型2

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<int> warp_shuffle_xor(
    int value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### 原型3

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<long long> warp_shuffle_xor(
    long long value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### 原型4

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<unsigned int> warp_shuffle_xor(
    unsigned int value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### 原型5

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<unsigned long long> warp_shuffle_xor(
    unsigned long long value, int xor_mask, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号xor xor_mask的Lane。 |
| `xor_mask` | 输入 | 与本Lane编号（0起）按位异或得到目标Lane编号的掩码。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号xor xor_mask的Lane。 |
| `xor_mask` | 输入 | 与本Lane编号（0起）按位异或得到目标Lane编号的掩码。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号xor xor_mask的Lane。 |
| `xor_mask` | 输入 | 与本Lane编号（0起）按位异或得到目标Lane编号的掩码。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号xor xor_mask的Lane。 |
| `xor_mask` | 输入 | 与本Lane编号（0起）按位异或得到目标Lane编号的掩码。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号xor xor_mask的Lane。 |
| `xor_mask` | 输入 | 与本Lane编号（0起）按位异或得到目标Lane编号的掩码。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::warp_shuffle_result<float>` | 返回按指定线程束来源位置取得的值。 |
| 原型2 | `asc::warp_shuffle_result<int>` | 返回按指定线程束来源位置取得的值。 |
| 原型3 | `asc::warp_shuffle_result<long long>` | 返回按指定线程束来源位置取得的值。 |
| 原型4 | `asc::warp_shuffle_result<unsigned int>` | 返回按指定线程束来源位置取得的值。 |
| 原型5 | `asc::warp_shuffle_result<unsigned long long>` | 返回按指定线程束来源位置取得的值。 |

## 约束说明

- 必须先检查返回的valid，再使用data；来源不属于同一Width分组、不是活动参与者或不在有效Lane范围时，data不作为有效结果使用。
- source_lane是组内索引；delta须非负且目标仍在当前组内；xor_mask须使目标位于同组。参与者掩码和调用位置须在参与Lane间收敛一致。

- 仅可在AI Core SIMT编程中调用。
- 所有参与的活动线程必须以收敛控制流调用。
- Width只能取1、2、4、8、16或32。

## 调用示例

以1个Block、32个线程收敛启动，output是至少32项的GM数组。每Lane输入为lane+1，Host同步后32项均应为1；无效来源不读取data。完整启动和读回工程见[Warp集体操作示例](../../../../examples/warp_collectives/README.md)。

```cpp
#include <asc/warp>
__global__ void example(unsigned int* output)
{
    const unsigned lane = asc::lane_id();
    const float value = static_cast<float>(lane + 1u);
    const auto result = asc::warp_shuffle_xor<32>(value, 1, asc::lane_mask::all());
    const bool expected_valid = true;
    output[lane] =
        result.valid == expected_valid && (!result.valid || result.data == static_cast<float>((lane ^ 1u) + 1u)) ? 1u :
                                                                                                                   0u;
}
```

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
