# asc::parallel::generate_n

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

Header: `<asc/algorithm>`.

`asc::parallel::generate_n` asynchronously invokes the generator the specified number of times and writes the results, in order, into the destination range.

## Function Prototype

```cpp
namespace asc::parallel {
template <class Output, class Size, class Generator>
asc::execution_status generate_n(asc::device_policy policy, Output first, Size count, Generator generator) noexcept;
}  // namespace asc::parallel
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Output` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `Size` | Type or compile-time value that represents the number of elements, the dimension, the bit width, or the index, as determined by the declaration. |
| `Generator` | Generator type that produces one output element value per no-argument call. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `policy` | Input | Device execution policy used to specify the stream, temporary storage, and execution requirements. |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `count` | Input | Number of elements participating in the operation. |
| `generator` | Input | No-argument callable object that returns a value assignable to the destination elements; it may produce constants or business data and is not required to be random. Each device thread keeps its own copy of the object and must not rely on a single serial call order. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the parameter validation or task submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- The public frontend requires a Clang-compatible ASC translation unit and an explicit definition of `CANN_ASC_STL_USE_SIMT_LAUNCH`; the value 1 selects SIMT and the value 0 selects SIMD. When it is not defined, these parallel names are not provided.

- All GM ranges of the inputs and outputs, scalar results, and the temporary storage actually consumed must remain valid from before submission until the stream task completes. Function objects are copied by value, but the device pointers they capture are also subject to the same lifetime constraint.
- Before synchronization or a correctly established dependency, the Host or other streams must not read, write, or release this storage; a successful execution_status return only means the work was submitted, not that the results are readable.

- The paths on this page currently do not use the policy temporary storage; passing an empty temporary storage does not by itself cause the submission to be rejected. If the caller reuses the same policy to run other operations that require a workspace, the capacity and alignment requirements of those operations must be observed separately.

- Uses C++17 and submits from the Host side of a BiSheng ASC translation unit.
- Input ranges must be contiguous, support random access, and be accessible by the device.
- Callable objects and transferred values must be trivially copyable and invocable on the AI Core.
- The policy must be bound to a valid stream; most current element-by-element or sequential paths do not consume temporary storage, and extra scratch should not be allocated for these paths.
- Scalar, count, or index outputs are located in GM and must remain valid until the stream completes.
- Only conditions that the implementation can determine, such as the stream and some output null pointers, are checked; range validity, device accessibility, address spaces, and lifetimes are caller preconditions, and there is no guarantee that an arbitrary invalid address returns an error before submission.

## Example

The following snippet uses the complete project's Host resource context: initial is [1, 2, 3, 4] and the second range is [1, 2, 3, 4]; prepare synchronously uploads to GM, complete checks the submission status and waits for the stream with a bounded wait, and read reads back only after completion. The code checks each independent expected result item by item.

For the complete project, task/stream/process time limits, and per-case records, see [parallel algorithm examples](../../../../../zh/examples/parallel_algorithms/README.md).

```cpp
#include <asc/algorithm>
#include "parallel_example.h"

struct generator {
    __aicore__ int operator()() const
    {
        return 7;
    }
};

bool example(parallel_example_context& context)
{
    const int initial[] = {1, 2, 3, 4};
    const int second[] = {1, 2, 3, 4};
    if (!context.prepare(initial, second))
        return false;
    auto policy = context.policy();
    auto* output = context.output;
    const auto status = asc::parallel::generate_n(policy, output, 4, generator{});
    if (!context.complete(status))
        return false;
    int actual[4]{};
    const int expected[] = {7, 7, 7, 7};
    if (!context.read(context.output, actual))
        return false;
    for (unsigned index = 0; index < 4; ++index) {
        if (actual[index] != expected[index])
            return false;
    }
    return true;
}
```

## Related APIs

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md): Parameter validation and task submission status; a successful submission does not mean the asynchronous work has completed.
- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): Device execution policy that specifies the stream, temporary storage, and execution requirements.
