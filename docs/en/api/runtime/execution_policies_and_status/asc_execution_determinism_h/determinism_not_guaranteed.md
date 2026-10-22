# asc::determinism::not_guaranteed

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

`asc::determinism::not_guaranteed` indicates that a parallel algorithm is not required to guarantee repeatable results for identical inputs.

This interface is available on Host.

## Declaration

Member of: [`asc::determinism`](determinism.md).

```cpp
// Excerpt of the declaration inside asc::determinism; template parameters and other members are provided by the enclosing class.
not_guaranteed;
```

## Constraints

- Only three values are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution.determinism.h>

auto value = asc::determinism::not_guaranteed;
```

## Related APIs

- [`asc::determinism`](determinism.md)
- [API list for this header](asc_execution_determinism_h.md)
