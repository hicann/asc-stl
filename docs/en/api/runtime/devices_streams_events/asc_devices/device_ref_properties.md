# asc::device_ref::properties

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

`asc::device_ref::properties` queries the properties of this device from the Runtime; the output object is updated and true is returned only when all properties are read successfully and the values are valid.

## Function Prototype

Member of: [`asc::device_ref`](device_ref.md).

```cpp
// Excerpt of the declaration inside asc::device_ref; template parameters and other members are provided by the owning class.
bool properties(asc::device_properties& output) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Provides the object reference used to "query the properties of this device from the Runtime"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Devices can only be queried or selected on the Host.
- A reference stores only the device ordinal and does not own Runtime state.
- On a failed query, the output parameter keeps its original value; the properties are limited to the AI Core, Vector Core, Warp, UB, GM, L2, and architecture fields listed by the current interface.

## Example

The following Host snippet demonstrates the call with a concrete object; when resource operations are involved, the initialization and lifetime constraints on this page must be followed.

```cpp
#include <asc/devices>

decltype(auto) example(asc::device_ref device)
{
    asc::device_properties properties{};
    return device.properties(properties);
}
```

## Related APIs

- [`asc::device_ref`](device_ref.md)
- [API list for this header](asc_devices.md)
