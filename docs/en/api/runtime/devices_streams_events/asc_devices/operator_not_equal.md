# `asc::operator!=` (Function)

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

Headers: `<asc/devices>`, `<asc/stream>`.

`asc::operator!=` determines whether the ordinals of two device references, or the native handles stored by two stream/event references, differ.

## Function Prototype

### Prototype 1

```cpp
constexpr bool asc::operator!=(asc::device_ref lhs, asc::device_ref rhs) noexcept;
```

This prototype corresponds to the header `<asc/devices>`.

### Prototype 2

```cpp
constexpr bool asc::operator!=(asc::event_ref lhs, asc::event_ref rhs) noexcept;
```

This prototype corresponds to the header `<asc/stream>`.

### Prototype 3

```cpp
constexpr bool asc::operator!=(asc::stream_ref lhs, asc::stream_ref rhs) noexcept;
```

This prototype corresponds to the header `<asc/stream>`.

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left device reference in the comparison: inequality is determined by the device ordinals of the two references. |
| `rhs` | Input | Right device reference in the comparison: inequality is determined by the device ordinals of the two references. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left event reference in the comparison: difference is determined by the native event handles stored by each reference. |
| `rhs` | Input | Right event reference in the comparison: difference is determined by the native event handles stored by each reference. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left stream reference in the comparison: difference is determined by the native stream handles stored by each reference. |
| `rhs` | Input | Right stream reference in the comparison: difference is determined by the native stream handles stored by each reference. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 2 | `bool` | Returns `true` when the condition holds, otherwise `false`. |
| Prototype 3 | `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- This page describes stored device property values, architecture enumerators, or ordinal comparison; observing these values does not query the Runtime.
- For initialization and device-availability requirements when obtaining actual device properties, see `device_ref::properties`; comparing ordinals does not prove that the corresponding device actually exists.

## Example

The following Host example compares references by their stored ordinals; operator syntax is used so that the hidden friends participate in resolution through argument-dependent lookup.

```cpp
#include <asc/devices>
bool example()
{
    asc::device_ref left(0);
    asc::device_ref same(0);
    asc::device_ref other(1);
    return left == same && left != other;
}
```

## Related APIs

- [API list for this header](asc_devices.md)
