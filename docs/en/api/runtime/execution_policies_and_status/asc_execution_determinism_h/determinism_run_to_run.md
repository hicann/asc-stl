# asc::determinism::run_to_run

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

Header: `<asc/execution.determinism.h>`.

`asc::determinism::run_to_run` requires that identical inputs produce repeatable results across multiple executions.

This interface is available on Host.

## Declaration

Member of: [`asc::determinism`](determinism.md).

```cpp
// Excerpt of the declaration inside asc::determinism; template parameters and other members are provided by the enclosing class.
run_to_run;
```

## Constraints

- Only three values are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution.determinism.h>

constexpr auto value = asc::determinism::run_to_run;
static_assert(value != asc::determinism::device_to_device, "documented states are distinct");
static_assert(value != asc::determinism::not_guaranteed, "documented states are distinct");
```

## Related APIs

- [`asc::determinism`](determinism.md)
- [API list for this header](asc_execution_determinism_h.md)
