# asc::execution::device

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

`asc::execution::device` is the default-constructed device execution policy object; a Stream, temporary storage, and execution requirements can be bound through chained calls.

This interface is available on Host.

## Declaration

```cpp
namespace asc::execution {
inline constexpr asc::device_policy device;
}  // namespace asc::execution
```

## Constraints

- The binding is immutable and does not own resources.
- Default construction binds an empty Stream, empty temporary storage, and default execution requirements.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution.policy.h>

auto value = asc::execution::device;
```

## Related APIs

- [`asc::device_policy`](device_policy.md): The device execution policy that specifies the Stream, temporary storage, and execution requirements.
