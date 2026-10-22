# asc::args::immediate::value

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

`asc::args::immediate::value` returns a reference to the immediate value inside the wrapper; the lifetime of the reference does not exceed that of the wrapper, and the survival of the original input object cannot extend this reference.

## Function Prototype

Member of: [`asc::args::immediate`](args_immediate.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::args::immediate; template parameters and other members are provided by the owning class.
constexpr T& value() & noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::args::immediate; template parameters and other members are provided by the owning class.
constexpr const T& value() const& noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

No parameters.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T&` | Returns a reference to the immediate value inside the wrapper; the lifetime of the reference does not exceed that of the wrapper, and the survival of the original input object cannot extend this reference. |
| Prototype 2 | `const T&` | Returns a reference to the immediate value inside the wrapper; the lifetime of the reference does not exceed that of the wrapper, and the survival of the original input object cannot extend this reference. |

## Constraints

- The immediate value and Bounds are stored by value inside the wrapper; no_bounds, static_bounds, or runtime_bounds may be stored, and reading the value does not automatically validate the bounds.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/argument>

bool example()
{
    asc::args::immediate<int> argument(7, asc::args::no_bounds{});
    return argument.value() == 7;
}
```

## Related APIs

- [`asc::args::immediate`](args_immediate.md)
- [API list for this header](asc_argument.md)
