# asc::output_ordering::stable_sorted

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

Header: `<asc/execution.output_ordering.h>`.

`asc::output_ordering::stable_sorted` requires the output to be ordered and to keep the original relative order of equivalent elements.

This interface is available on Host.

## Declaration

Member of: [`asc::output_ordering`](output_ordering.md).

```cpp
// Excerpt of the declaration inside asc::output_ordering; template parameters and other members are provided by the enclosing class.
stable_sorted;
```

## Constraints

- Only three values are provided.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution.output_ordering.h>

auto value = asc::output_ordering::stable_sorted;
```

## Related APIs

- [`asc::output_ordering`](output_ordering.md)
- [API list for this header](asc_execution_output_ordering_h.md)
