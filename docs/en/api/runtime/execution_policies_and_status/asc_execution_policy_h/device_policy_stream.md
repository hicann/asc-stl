# asc::device_policy::stream

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

`asc::device_policy::stream` returns the non-owning Stream reference bound to the current policy.

This interface is available on Host.

## Function Prototype

Member of: [`asc::device_policy`](device_policy.md).

```cpp
// Excerpt of the declaration inside asc::device_policy; template parameters and other members are provided by the enclosing class.
constexpr asc::stream_ref stream() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::stream_ref` | Returns the non-owning Stream reference bound to the current policy. |

## Constraints

- The binding is immutable and does not own resources.
- Default construction binds an empty Stream, empty temporary storage, and default execution requirements.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/execution.policy.h>

bool example()
{
    asc::device_policy policy;
    return !policy.stream() && policy.temporary_storage().data() == nullptr
        && policy.temporary_storage().size_bytes() == 0
        && policy.requirements().determinism_value() == asc::determinism::not_guaranteed;
}
```

## Related APIs

- [`asc::device_policy`](device_policy.md): The device execution policy that specifies the Stream, temporary storage, and execution requirements.
