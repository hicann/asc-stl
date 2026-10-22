# asc::npu_arch

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

`asc::npu_arch` represents the NPU architecture number queried from the Runtime; numbers that cannot be recognized are mapped to `unknown`.

## Declaration

```cpp
namespace asc {
enum class npu_arch : asc::std::uint32_t;
}  // namespace asc
```

## Constraints

- This page describes stored device property values, architecture enumerators, or ordinal comparison; observing these values does not query the Runtime.
- For initialization and device-availability requirements when obtaining actual device properties, see `device_ref::properties`; comparing ordinals does not prove that the corresponding device actually exists.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/devices>

bool example()
{
    // Default properties are empty values before the query and do not represent the specifications of any real device.
    asc::device_properties properties{};
    return properties.architecture == asc::npu_arch::unknown;
}
```

## Related APIs

- [API list for this header](asc_devices.md)
