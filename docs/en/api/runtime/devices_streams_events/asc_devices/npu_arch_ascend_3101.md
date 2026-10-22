# asc::npu_arch::ascend_3101

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

Header: `<asc/devices>`.

`asc::npu_arch::ascend_3101` represents an NPU with architecture number 3101.

## Declaration

Member of: [`asc::npu_arch`](npu_arch.md).

```cpp
// Excerpt of the declaration inside asc::npu_arch; template parameters and other members are provided by the owning class.
ascend_3101 = 3101;
```

## Constraints

- This page describes stored device property values, architecture enumerators, or ordinal comparison; observing these values does not query the Runtime.
- For initialization and device-availability requirements when obtaining actual device properties, see `device_ref::properties`; comparing ordinals does not prove that the corresponding device actually exists.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/devices>

auto value = asc::npu_arch::ascend_3101;
```

## Related APIs

- [`asc::npu_arch`](npu_arch.md)
- [API list for this header](asc_devices.md)
