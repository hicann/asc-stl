# asc::parallel::merge

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

`asc::parallel::merge` asynchronously merges two sorted input ranges and preserves an ordered result under the given comparison relation.

## Function Prototype

```cpp
namespace asc::parallel {
template <class Input1, class Input2, class Output, class Compare>
asc::execution_status merge(asc::device_policy policy, Input1 first1, Input1 last1, Input2 first2, Input2 last2,
    Output result, Compare compare) noexcept;
}  // namespace asc::parallel
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Input1` | Iterator type used to read the input range elements; must satisfy the traversal capability required by the prototype. |
| `Input2` | Iterator type used to read the input range elements; must satisfy the traversal capability required by the prototype. |
| `Output` | Iterator type used to write the result range; the destination storage must have sufficient capacity. |
| `Compare` | Comparison object type that defines the order of the elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `policy` | Input | Device execution policy (device_policy): provides the stream used for task submission and the caller's temporary storage; the return value reflects only the submission status, and a successful submission does not mean the asynchronous work has completed. |
| `first1` | Input | Iterator or pointer to the start of the first sorted input range. |
| `last1` | Input | End position of the first sorted input range, not included. |
| `first2` | Input | Iterator or pointer to the start of the second sorted input range. |
| `last2` | Input | End position of the second sorted input range, not included. |
| `result` | Output | Iterator to the start of the output range: the two-way merge result is written asynchronously through this range, whose capacity must not be less than the sum of the lengths of the two input ranges. |
| `compare` | Input | Comparison object: when compare(a, b) is true, a is placed before b, and the two input ranges and the output must preserve the same order relation; must be trivially copyable and invocable on the AI Core. |

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

The following snippet uses the complete project's Host resource context: initial is [1, 2, 3, 4] and the second range is [2, 4, 6, 8]; prepare synchronously uploads to GM, complete checks the submission status and waits for the stream with a bounded wait, and read reads back only after completion. The code checks each independent expected result item by item.

For the complete project, task/stream/process time limits, and per-case records, see [parallel algorithm examples](../../../../../zh/examples/parallel_algorithms/README.md).

```cpp
#include <asc/algorithm>
#include "parallel_example.h"

struct compare {
    __aicore__ bool operator()(int left, int right) const
    {
        return left < right;
    }
};

bool example(parallel_example_context& context)
{
    const int initial[] = {1, 2, 3, 4};
    const int second[] = {2, 4, 6, 8};
    if (!context.prepare(initial, second))
        return false;
    auto policy = context.policy();
    auto* input = context.input;
    auto* other = context.other;
    auto* output = context.output;
    const auto status = asc::parallel::merge(policy, input, input + 4, other, other + 4, output, compare{});
    if (!context.complete(status))
        return false;
    int actual[8]{};
    const int expected[] = {1, 2, 2, 3, 4, 4, 6, 8};
    if (!context.read(context.output, actual))
        return false;
    for (unsigned index = 0; index < 8; ++index) {
        if (actual[index] != expected[index])
            return false;
    }
    return true;
}
```

## Related APIs

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md): Parameter validation and task submission status; a successful submission does not mean the asynchronous work has completed.
- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md): Device execution policy that specifies the stream, temporary storage, and execution requirements.
