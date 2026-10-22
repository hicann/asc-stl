# asc::pinned_memory_resource_ref::deallocate

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

`asc::pinned_memory_resource_ref::deallocate` forwards to the referenced resource to release page-locked Host memory; an invalid reference returns a parameter error.

## Function Prototype

Member of: [`asc::pinned_memory_resource_ref`](pinned_memory_resource_ref.md).

```cpp
// Excerpt of the declaration inside class asc::pinned_memory_resource_ref; template parameters and other members are provided by the owning class.
asc::execution_status deallocate(void* pointer, asc::std::size_t bytes, asc::std::size_t alignment = alignof(asc::std::max_align_t)) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Address previously allocated by the corresponding resource and not yet released; a non-null address must match the byte count, alignment, and device ownership of this call. Releasing a null pointer on a valid resource is a no-op; an invalid resource reference still returns a parameter error. |
| `bytes` | Input | The number of bytes originally requested for the allocation; it must match the one used at allocation. |
| `alignment` | Input | Byte alignment value; it must be a non-negative integer power of two and must not exceed `alignof(asc::std::max_align_t)`; it must match the original allocation and is validated only when releasing a non-null address. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the status of this synchronous release; on success this operation has already completed. |

## Constraints

- May only be called on Host; the runtime must already be initialized.
- This interface does not throw exceptions; failures are reported through `asc::execution_status`.
- The referenced resource must remain valid for the duration of this call. An invalid reference returns `asc::execution_errc::invalid_argument`.
- A valid resource returns success directly when releasing `nullptr`, without validating `bytes` or `alignment`.
- A non-null address must come from the same resource and not have been released yet; `bytes` and `alignment` must match those used at allocation.
- For a non-null address, `bytes` must be greater than 0 and `alignment` must be a non-negative integer power of two and must not exceed `alignof(asc::std::max_align_t)`. If the parameters are not satisfied, `asc::execution_errc::invalid_argument` is returned and no release is performed.
- Before the call, asynchronous tasks using the allocation must have completed; on release failure the status must be handled and the address must not be treated as already released.

## Example

The following Host snippet demonstrates the call with concrete objects; resource operations must follow the initialization and lifetime constraints on this page.

```cpp
#include <asc/memory_resource>

decltype(auto) example(asc::pinned_memory_resource_ref& resource, void* pointer)
{
    // pointer must be an address previously allocated successfully from the same resource.
    return resource.deallocate(pointer, 64);
}
```

## Related APIs

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Parameter-validation and task-submission status; a successful submission does not mean the asynchronous work has completed.
