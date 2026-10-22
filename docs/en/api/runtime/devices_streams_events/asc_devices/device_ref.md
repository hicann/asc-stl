# asc::device_ref

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

`asc::device_ref` is a lightweight value object that identifies a device by its Runtime ordinal; it can query the ordinal and device properties, and it does not own Runtime device resources.

## Declaration

```cpp
namespace asc {
class device_ref;
} // namespace asc
```

## Constraints

- Devices can only be queried or selected on the Host.
- A reference stores only the device ordinal and does not own Runtime state.
- On a failed query, the output parameter keeps its original value; the properties are limited to the AI Core, Vector Core, Warp, UB, GM, L2, and architecture fields listed by the current interface.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/devices>

bool example()
{
    asc::device_ref device(0);
    return device.ordinal() == 0;
}
```

## Related APIs

- [API list for this header](asc_devices.md)
