# asc::warp_shuffle_idx

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/warp>`.

`asc::warp_shuffle_idx` reads the value of the specified source lane in the same group.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<float> warp_shuffle_idx(
    float value, int source_lane, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<int> warp_shuffle_idx(
    int value, int source_lane, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<long long> warp_shuffle_idx(
    long long value, int source_lane, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### Prototype 4

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<unsigned int> warp_shuffle_idx(
    unsigned int value, int source_lane, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

### Prototype 5

```cpp
namespace asc {
template <int Width = 32>
asc::warp_shuffle_result<unsigned long long> warp_shuffle_idx(
    unsigned long long value, int source_lane, asc::lane_mask participants = asc::lane_mask::all()) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Shuffle group width (compile-time integer, one of 1/2/4/8/16/32, default 32): lanes are grouped by Width, and the target lane must be in the same group as the calling lane. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the shuffle: the returned value comes from the lane whose index is source_lane. |
| `source_lane` | Input | The index of the source lane to read from within the current width group; this parameter is a scalar index and involves no storage lifetime. |
| `participants` | Input | Specifies the set of active lanes participating in the warp operation. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Shuffle group width (compile-time integer, one of 1/2/4/8/16/32, default 32): lanes are grouped by Width, and the target lane must be in the same group as the calling lane. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the shuffle: the returned value comes from the lane whose index is source_lane. |
| `source_lane` | Input | The index of the source lane to read from within the current width group; this parameter is a scalar index and involves no storage lifetime. |
| `participants` | Input | Specifies the set of active lanes participating in the warp operation. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Shuffle group width (compile-time integer, one of 1/2/4/8/16/32, default 32): lanes are grouped by Width, and the target lane must be in the same group as the calling lane. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the shuffle: the returned value comes from the lane whose index is source_lane. |
| `source_lane` | Input | The index of the source lane to read from within the current width group; this parameter is a scalar index and involves no storage lifetime. |
| `participants` | Input | Specifies the set of active lanes participating in the warp operation. |

### Parameters of Prototype 4

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Shuffle group width (compile-time integer, one of 1/2/4/8/16/32, default 32): lanes are grouped by Width, and the target lane must be in the same group as the calling lane. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the shuffle: the returned value comes from the lane whose index is source_lane. |
| `source_lane` | Input | The index of the source lane to read from within the current width group; this parameter is a scalar index and involves no storage lifetime. |
| `participants` | Input | Specifies the set of active lanes participating in the warp operation. |

### Parameters of Prototype 5

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Width` | Shuffle group width (compile-time integer, one of 1/2/4/8/16/32, default 32): lanes are grouped by Width, and the target lane must be in the same group as the calling lane. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the shuffle: the returned value comes from the lane whose index is source_lane. |
| `source_lane` | Input | The index of the source lane to read from within the current width group; this parameter is a scalar index and involves no storage lifetime. |
| `participants` | Input | Specifies the set of active lanes participating in the warp operation. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::warp_shuffle_result<float>` | Returns the value obtained from the specified warp source position. |
| Prototype 2 | `asc::warp_shuffle_result<int>` | Returns the value obtained from the specified warp source position. |
| Prototype 3 | `asc::warp_shuffle_result<long long>` | Returns the value obtained from the specified warp source position. |
| Prototype 4 | `asc::warp_shuffle_result<unsigned int>` | Returns the value obtained from the specified warp source position. |
| Prototype 5 | `asc::warp_shuffle_result<unsigned long long>` | Returns the value obtained from the specified warp source position. |

## Constraints

- The returned valid must be checked before data is used; when the source is not in the same Width group, is not an active participant, or is outside the valid lane range, data is not used as a valid result.
- source_lane is an index within the group; delta must be non-negative and the target must remain in the current group; xor_mask must keep the target in the same group. The participant mask and call site must be converged and consistent across the participating lanes.

- Can only be called in AI Core SIMT programming.
- All participating active threads must call it in converged control flow.
- Width can only be 1, 2, 4, 8, 16, or 32.

## Example

Launched converged with 1 block and 32 threads; output is a GM array of at least 32 elements. Each lane's input is lane+1; after Host synchronization all 32 elements should be 1; data is not read for invalid sources. For the complete launch and read-back project, see the [warp collectives example](../../../../../../examples/extension/warp_collectives/README_en.md).

```cpp
#include <asc/warp>
__global__ void example(unsigned int* output)
{
    const unsigned lane = asc::lane_id();
    const float value = static_cast<float>(lane + 1u);
    const auto result = asc::warp_shuffle_idx<32>(value, 0, asc::lane_mask::all());
    const bool expected_valid = true;
    output[lane] = result.valid == expected_valid && (!result.valid || result.data == static_cast<float>(1u)) ? 1u : 0u;
}
```

## Related APIs

- [`asc::lane_mask`](lane_mask.md): A bit set of lanes in a warp; bit i corresponds to the lane numbered i.
