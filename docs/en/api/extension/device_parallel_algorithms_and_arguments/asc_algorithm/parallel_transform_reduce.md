# asc::parallel::transform_reduce

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

`asc::parallel::transform_reduce` asynchronously transforms the input elements and reduces the transform results, finally writing the single result to a GM output parameter.

The interface specifies the stream, temporary storage, and execution requirements through [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md) and asynchronously submits a device task; the returned [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md) indicates the parameter validation and task submission status, and a successful submission does not mean the asynchronous execution has completed.

## Function Prototype

```cpp
namespace asc::parallel {
template <class Input, class T, class BinaryOperation, class UnaryOperation>
asc::execution_status transform_reduce(asc::device_policy policy, Input first, Input last, T init, T* output_value,
    BinaryOperation binary_operation, UnaryOperation unary_operation) noexcept;
}  // namespace asc::parallel
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Input` | Iterator type used to read the input range elements; must satisfy the traversal capability required by the prototype. |
| `T` | Type of the input range elements or of the values participating in the operation. |
| `BinaryOperation` | Callable object type that performs the operation on this page on the input values. |
| `UnaryOperation` | Callable object type that performs the operation on this page on the input values. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `policy` | Input | Device execution policy (device_policy): provides the stream used for task submission and the caller's temporary storage; the return value reflects only the submission status, and a successful submission does not mean the asynchronous work has completed. |
| `first` | Input | Iterator or pointer to the start of the input range. |
| `last` | Input | End position of the input range, not included. |
| `init` | Input | Provides the initial reduction value; the initial value also determines the type `T` of the reduction result and the intermediate accumulator, and for an empty range the result is `init`. |
| `output_value` | Output | GM address used to receive the reduction result; the result type is `T`, determined by the initial value and the binary operation. The reduction result is written asynchronously by the device and must be read after the stream is synchronized and the result is ready; the address must remain valid until the asynchronous task completes. |
| `binary_operation` | Input | Provides the binary operation that accepts the current accumulator value and one transform result and returns the new accumulator value; the reduction result is obtained by folding the transform results of the elements one by one into the initial value through this operation. |
| `unary_operation` | Input | Provides the unary transform operation that accepts one input element and returns the transform result participating in the reduction. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the parameter validation or task submission status, not the reduction result; a successful submission does not mean the reduction result is ready, and before reading `*output_value` you must synchronize and wait for the stream bound to the policy to complete. |

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

struct binary_operation {
    __aicore__ int operator()(int left, int right) const
    {
        return left + right;
    }
};
struct unary_operation {
    __aicore__ int operator()(int value) const
    {
        return value * 2;
    }
};

bool example(parallel_example_context& context)
{
    const int initial[] = {1, 2, 3, 4};
    const int second[] = {1, 2, 3, 4};
    if (!context.prepare(initial, second))
        return false;
    auto policy = context.policy();
    auto* input = context.input;
    auto* output = context.output;
    const auto status =
        asc::parallel::transform_reduce(policy, input, input + 4, 0, output, binary_operation{}, unary_operation{});
    if (!context.complete(status))
        return false;
    int actual[1]{};
    const int expected[] = {20};
    if (!context.read(context.output, actual))
        return false;
    for (unsigned index = 0; index < 1; ++index) {
        if (actual[index] != expected[index])
            return false;
    }
    return true;
}
```

## Related APIs

- [API list for this header](asc_algorithm.md)
