# asc::launch

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

Header: `<asc/launch>`.

`asc::launch` asynchronously launches a compile-time-determined SIMT or AICore kernel on the specified Stream. A success status indicates that the launch has been submitted; all kernel arguments passed by value must be trivially copyable.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
template <auto Kernel, class... Args>
asc::execution_status launch(asc::stream_ref stream, asc::aicore_launch_config config, Args... args) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
template <auto Kernel, class... Args>
asc::execution_status launch(asc::stream_ref stream, asc::simt_launch_config config, Args... args) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Kernel` | The compile-time-determined device kernel function entry point. |
| `Args` | The list of argument types passed by value to the kernel function; every type must be trivially copyable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | The Stream that receives this launch task; after submission the task executes in this Stream's order, and the Stream must remain valid until completion. |
| `config` | Input | The launch configuration of the AI Core SIMD programming kernel function, specifying the execution blocks required. |
| `args` | Input | The by-value arguments passed to the kernel function; they must not reference invalidated external resources during execution after submission. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Kernel` | The compile-time-determined device kernel function entry point. |
| `Args` | The list of argument types passed by value to the kernel function; every type must be trivially copyable. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | The Stream that receives this launch task; after submission the task executes in this Stream's order, and the Stream must remain valid until completion. |
| `config` | Input | The launch configuration of the AI Core SIMT programming kernel function, specifying the grid, thread blocks, and dynamic shared memory. |
| `args` | Input | The by-value arguments passed to the kernel function; they must not reference invalidated external resources during execution after submission. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::execution_status` | Returns the argument validation or task submission status; a successful submission does not mean the asynchronous work has completed. |
| Prototype 2 | `asc::execution_status` | Returns the argument validation or task submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- These kernel submission overloads require a Clang-compatible BiSheng ASC translation unit and an explicit definition of `CANN_ASC_STL_USE_SIMT_LAUNCH`.
- When the macro value is non-zero, only the `simt_launch_config` overload is provided; when it is zero, only the `aicore_launch_config` overload is provided; when it is undefined, neither is provided. Select the corresponding configuration according to the actual compilation mode.

- Can only be called in the Host submission phase of a BiSheng ASC translation unit.
- The compile-time Kernel template argument must be specified explicitly at the call, the Stream and launch dimensions must be valid, and the arguments passed by value must be trivially copyable.
- Success only indicates that the task has been submitted.
- Can only be called on the Host.
- Kernel must be a compile-time-determined target, and the arguments are passed by value and must be trivially copyable.
- The Stream, launch dimensions, and argument lifetimes must be valid.
- Success only indicates that the task has been submitted in Stream order.

## Example

The following snippet is used in a BiSheng ASC translation unit: the Host submits an ordinary AI Core kernel with a valid Stream, and output points to valid global memory.

```cpp
#include <asc/launch>

extern "C" __global__ __vector__ void example_kernel(__gm__ int* output)
{
    output[0] = 7;
}
decltype(auto) example(asc::stream_ref stream, int* output)
{
    return asc::launch<example_kernel>(stream, asc::aicore_launch_config{1}, output);
}
```

## Related APIs

- [asc::stream_ref](../../devices_streams_events/asc_stream/stream_ref.md)
- [asc::aicore_launch_config](aicore_launch_config.md)
- [asc::simt_launch_config](simt_launch_config.md)
- [asc::execution_status](../../execution_policies_and_status/asc_execution/execution_status.md)
