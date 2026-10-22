# asc::device_ref::ordinal

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

`asc::device_ref::ordinal` returns the Runtime device ordinal stored by this reference.

## Function Prototype

Member of: [`asc::device_ref`](device_ref.md).

```cpp
// Excerpt of the declaration inside asc::device_ref; template parameters and other members are provided by the owning class.
constexpr asc::std::uint32_t ordinal() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::uint32_t` | Returns the Runtime device ordinal stored by this reference. |

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

- [`asc::device_ref`](device_ref.md)
- [API list for this header](asc_devices.md)
