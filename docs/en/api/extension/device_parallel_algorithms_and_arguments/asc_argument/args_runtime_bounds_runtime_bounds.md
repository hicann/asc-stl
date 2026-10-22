# asc::args::runtime_bounds::runtime_bounds

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

Header: `<asc/argument>`.

`asc::args::runtime_bounds::runtime_bounds` initializes an `asc::args::runtime_bounds` object with the caller-provided arguments.

## Function Prototype

Member of: [`asc::args::runtime_bounds`](args_runtime_bounds.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::args::runtime_bounds; template parameters and other members are provided by the owning class.
constexpr runtime_bounds() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::args::runtime_bounds; template parameters and other members are provided by the owning class.
constexpr runtime_bounds(T lower, T upper) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lower` | Input | Lower bound of the runtime argument bounds: stored in the object and queried through lower(). |
| `upper` | Input | Upper bound of the runtime argument bounds: stored in the object and queried through upper(). |

## Return Value

No return value.

## Constraints

- Runtime bounds are stored by value, and the caller must ensure that lower is not greater than upper; construction and queries perform no argument range check. For compile-time bounds, Lower must not be greater than Upper.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/argument>

bool example()
{
    asc::args::runtime_bounds<int> bounds(2, 8);
    return bounds.lower() == 2 && bounds.upper() == 8;
}
```

## Related APIs

- [`asc::args::runtime_bounds`](args_runtime_bounds.md)
- [API list for this header](asc_argument.md)
