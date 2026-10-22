# CANN_ASC_STL_HAS_DEVICE_POLICY

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

Header: `<asc/version>`.

`CANN_ASC_STL_HAS_DEVICE_POLICY` is defined as 1, indicating that the current version provides the complete Device execution policy and the immutable execution requirement interfaces.

## Declaration

```cpp
#define CANN_ASC_STL_HAS_DEVICE_POLICY 1
```

## Constraints

- Provides the product version and delivered-capability macros.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/version>

#ifndef CANN_ASC_STL_HAS_DEVICE_POLICY
#error "CANN_ASC_STL_HAS_DEVICE_POLICY is required by this public Header"
#endif
```

## Related APIs

- [API list for this header](asc_version.md)
