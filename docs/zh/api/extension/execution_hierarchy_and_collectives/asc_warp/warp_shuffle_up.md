# asc::warp_shuffle_up

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

`asc::warp_shuffle_up`读取同一分组中Lane编号减少delta后的值。

## 函数原型

### 原型1

```cpp
namespace asc {
template<int Width = 32> asc::warp_shuffle_result<float> warp_shuffle_up(float value, int delta, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### 原型2

```cpp
namespace asc {
template<int Width = 32> asc::warp_shuffle_result<int> warp_shuffle_up(int value, int delta, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### 原型3

```cpp
namespace asc {
template<int Width = 32> asc::warp_shuffle_result<long long> warp_shuffle_up(long long value, int delta, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### 原型4

```cpp
namespace asc {
template<int Width = 32> asc::warp_shuffle_result<unsigned int> warp_shuffle_up(unsigned int value, int delta, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
```

### 原型5

```cpp
namespace asc {
template<int Width = 32> asc::warp_shuffle_result<unsigned long long> warp_shuffle_up(unsigned long long value, int delta, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
} // namespace asc
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
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号 - delta的Lane。 |
| `delta` | 输入 | 目标Lane相对本Lane编号的负向偏移量。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号 - delta的Lane。 |
| `delta` | 输入 | 目标Lane相对本Lane编号的负向偏移量。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号 - delta的Lane。 |
| `delta` | 输入 | 目标Lane相对本Lane编号的负向偏移量。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号 - delta的Lane。 |
| `delta` | 输入 | 目标Lane相对本Lane编号的负向偏移量。 |
| `participants` | 输入 | 参与本操作的Lane集合掩码（lane_mask，bit i对应Lane i，默认lane_mask::all()）：自身或目标不在集合内时结果无效。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Width` | 洗牌分组宽度（编译期整数，取1/2/4/8/16/32，默认32）：Lane按Width分组，目标Lane须与调用Lane同组。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 本Lane提供参与洗牌的值：返回值来自同一分组内编号为 本Lane编号 - delta的Lane。 |
| `delta` | 输入 | 目标Lane相对本Lane编号的负向偏移量。 |
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

- 仅可在AI Core SIMT编程中调用。
- 所有参与的活动线程必须以收敛控制流调用。
- Width只能取1、2、4、8、16或32。

## 调用示例

以下片段聚焦当前接口的调用；输入、资源和执行上下文须满足本页约束。

```cpp
#include <asc/warp>

template <int Width>
__aicore__ decltype(auto) example(float value, int delta, asc::lane_mask participants = asc::lane_mask::all())
{
    return asc::warp_shuffle_up<Width>(value, delta, participants);
}
```

对应完整工程使用`C++17`；请在目标工具链及设备上编译和运行。

完整示例源码：

- [CMakeLists.txt](../../../../examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../examples/warp_collectives/main.cpp)

## 关联API

- [`asc::lane_mask`](lane_mask.md)：Warp内Lane的位集合；第i位对应编号为i的Lane。
