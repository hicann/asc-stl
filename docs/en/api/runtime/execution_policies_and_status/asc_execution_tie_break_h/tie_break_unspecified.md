# asc::tie_break::unspecified

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

Header: `<asc/execution.tie_break.h>`.

`asc::tie_break::unspecified` indicates that no preferred selection rule is specified when multiple positions satisfy the condition at the same time.

This interface is available on Host.

## Declaration

Member of: [`asc::tie_break`](tie_break.md).

```cpp
// Excerpt of the declaration inside asc::tie_break; template parameters and other members are provided by the enclosing class.
unspecified;
```

## Constraints

- Only three values are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution.tie_break.h>

auto value = asc::tie_break::unspecified;
```

## Related APIs

- [`asc::tie_break`](tie_break.md)
- [API list for this header](asc_execution_tie_break_h.md)
