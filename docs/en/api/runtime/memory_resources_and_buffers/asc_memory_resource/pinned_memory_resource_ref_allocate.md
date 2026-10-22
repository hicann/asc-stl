# asc::pinned_memory_resource_ref::allocate

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

Header: `<asc/memory_resource>`.

`asc::pinned_memory_resource_ref::allocate` forwards to the referenced resource to allocate page-locked Host memory; an invalid reference returns a parameter error and nulls the output pointer when possible.

## Function Prototype

Member of: [`asc::pinned_memory_resource_ref`](pinned_memory_resource_ref.md).

```cpp
// Excerpt of the declaration inside class asc::pinned_memory_resource_ref; template parameters and other members are provided by the owning class.
asc::execution_status allocate(
    void** output, asc::std::size_t bytes, asc::std::size_t alignment = alignof(asc::std::max_align_t)) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Writable pointer slot that receives the allocated address; the slot itself is non-null and *output is nullptr before the call. On success the address allocated by the resource is written; on failure it is handled according to the returned status. |
| `bytes` | Input | Non-zero number of bytes requested this time. |
| `alignment` | Input | Byte alignment value; it must be a non-negative integer power of two and must not exceed `alignof(asc::std::max_align_t)`; the default value equals the upper limit. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the status of this synchronous allocation; on success this operation has already completed. |

## Constraints

- May only be called on Host; the runtime must already be initialized.
- This interface does not throw exceptions; failures are reported through `asc::execution_status`.
- The referenced resource must remain valid for the duration of this call. An invalid reference returns `asc::execution_errc::invalid_argument`.
- An invalid reference sets `*output` to `nullptr` when `output` is non-null; a valid reference forwards to the referenced resource.
- `output` must be non-null and `*output == nullptr` before the call; `bytes` must be greater than 0.
- `alignment` must be a non-negative integer power of two and must not exceed `alignof(asc::std::max_align_t)`. A valid resource returns `asc::execution_errc::invalid_argument` when the above parameter validation fails and does not write to `*output`.
- Underlying allocation failures are reported through the returned status; the caller uses the output address only after success.

## Example

The caller provides a valid resource and has completed Runtime initialization; the returned status indicates the cleanup result, and on failure pointer retains ownership of the 64-byte allocation, which the caller must retry releasing with the same resource.

```cpp
#include <asc/memory_resource>
struct allocation_result {
    void* pointer;
    asc::execution_status status;
};
allocation_result example(const asc::pinned_memory_resource_ref& resource)
{
    void* pointer = nullptr;
    const auto allocated = resource.allocate(&pointer, 64);
    if (!allocated.success())
        return {nullptr, allocated};
    const auto released = resource.deallocate(pointer, 64);
    // On failure, hand the still-owned address back to the caller, keeping the original resource for retry.
    return {released.success() ? nullptr : pointer, released};
}
```

## Related APIs

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Parameter-validation and task-submission status; a successful submission does not mean the asynchronous work has completed.
