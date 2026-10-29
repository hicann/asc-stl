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

This complete example uses the real CANN Runtime and selects device 0, which must be available before running. Asynchronous waits are limited to 10 seconds. Failure terminates the example process to avoid releasing resources still in use; the controller must stop subsequent tasks and recheck device health. On success, work completes before resources are closed, the device is reset, and the Runtime is finalized. Compile this mixed Host/AI Core translation unit in BiSheng ASC mode with `-DCANN_ASC_STL_USE_SIMT_LAUNCH=0`; the documentation gate records SIMD compilation only, not successful device execution.

```cpp
#include <acl/acl.h>
#include <asc/stream>
#include <cstdlib>

void check(bool condition)
{
    if (!condition) {
        std::_Exit(2);
    }
}

void finish(asc::stream_ref stream)
{
    check(aclrtSynchronizeStreamWithTimeout(stream.native_handle(), 10000) == ACL_SUCCESS);
}
#include <asc/launch>

extern "C" __global__ __vector__ void example_kernel(__gm__ int* output)
{
    output[0] = 7;
}

void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    void* device = nullptr;
    void* host = nullptr;
    check(aclrtMalloc(&device, sizeof(int), ACL_MEM_MALLOC_HUGE_FIRST) == ACL_SUCCESS);
    check(aclrtMallocHost(&host, sizeof(int)) == ACL_SUCCESS);
    check(asc::launch<example_kernel>(stream, asc::aicore_launch_config{1}, static_cast<int*>(device)).success());
    check(aclrtMemcpyAsync(host, sizeof(int), device, sizeof(int), ACL_MEMCPY_DEVICE_TO_HOST,
        stream.native_handle()) == ACL_SUCCESS);
    finish(stream);
    check(*static_cast<int*>(host) == 7);
    check(aclrtFreeHost(host) == ACL_SUCCESS && aclrtFree(device) == ACL_SUCCESS);
    check(stream.close());
}

int main()
{
    if (aclInit(nullptr) != ACL_SUCCESS) {
        return 1;
    }
    if (!asc::set_current_device(asc::device_ref(0))) {
        check(aclFinalize() == ACL_SUCCESS);
        return 1;
    }
    run_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return reset && finalized ? 0 : 1;
}
```

## Related APIs

- [asc::stream_ref](../../devices_streams_events/asc_stream/stream_ref.md)
- [asc::aicore_launch_config](aicore_launch_config.md)
- [asc::simt_launch_config](simt_launch_config.md)
- [asc::execution_status](../../execution_policies_and_status/asc_execution/execution_status.md)
