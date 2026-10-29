# asc::device_policy::with_temporary_storage

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

Header: `<asc/execution.policy.h>`.

`asc::device_policy::with_temporary_storage` returns a new policy bound to the specified temporary storage, keeping the Stream and execution requirements of the original policy.

This interface is available on Host.

## Function Prototype

Member of: [`asc::device_policy`](device_policy.md).

```cpp
// Excerpt of the declaration inside asc::device_policy; template parameters and other members are provided by the enclosing class.
constexpr asc::device_policy with_temporary_storage(asc::temporary_storage_ref storage) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `storage` | Input | The temporary storage provided by the caller; its capacity and lifetime must satisfy the constraints on this page. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::device_policy` | Returns a new policy bound to the specified temporary storage, keeping the Stream and execution requirements of the original policy. |

## Constraints

- Only the execution requirement, Stream, or temporary storage binding named by the function is replaced; the other policy attributes remain unchanged.

## Example

This Host example submits no Runtime work and checks configuration or resource-reference results using concrete values. The local storage is used only to check configuration; submitting a Device algorithm requires valid Device storage that remains alive until asynchronous work completes.

```cpp
#include <asc/execution.policy.h>

bool example()
{
    alignas(32) unsigned char bytes[128]{};
    const asc::temporary_storage_ref storage(bytes, sizeof(bytes), asc::memory_space::local);
    const auto base = asc::execution::device;
    const auto configured = base.with_temporary_storage(storage);
    return configured.temporary_storage().data() == bytes &&
        configured.temporary_storage().size_bytes() == 128 &&
        configured.temporary_storage().space() == asc::memory_space::local &&
        base.temporary_storage().empty();
}
```

## Related APIs

- [`asc::device_policy`](device_policy.md): The device execution policy that specifies the Stream, temporary storage, and execution requirements.
