# asc::warp_reduce_add

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

`asc::warp_reduce_add` sums `value` across all participating lanes in the current warp and returns the same reduction result to every participating lane. This interface performs the intra-warp addition reduction without going through global memory.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
float warp_reduce_add(float value) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
int warp_reduce_add(int value) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
unsigned int warp_reduce_add(unsigned int value) noexcept;
} // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the reduction. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the reduction. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The value this lane contributes to the reduction. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `float` | Returns the sum of the float input values of all participating lanes. |
| Prototype 2 | `int` | Returns the sum of the int input values of all participating lanes. |
| Prototype 3 | `unsigned int` | Returns the sum of the unsigned int input values of all participating lanes. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All participating active threads must call it in converged control flow.

## Example

The following AI Core SIMT snippet has each lane participate in the addition reduction with its own lane index and checks that all participating lanes obtain the same result.

```cpp
#include <asc/warp>

__aicore__ bool example()
{
    const unsigned int lane = asc::lane_id();
    const unsigned int sum = asc::warp_reduce_add(lane);

    // The lane indices of a full warp are 0 through 31, so the reduction result should be 496.
    return sum == 496U;
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source:

- [CMakeLists.txt](../../../../../zh/examples/warp_collectives/CMakeLists.txt)
- [warp_example.h](../../../../../zh/examples/warp_collectives/warp_example.h)
- [kernel.asc](../../../../../zh/examples/warp_collectives/kernel.asc)
- [main.cpp](../../../../../zh/examples/warp_collectives/main.cpp)

## Related APIs

- [API list for this header](asc_warp.md)
