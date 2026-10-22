# asc::args::constant::value

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

`asc::args::constant::value` returns the compile-time constant encoded in the type.

## Function Prototype

Member of: [`asc::args::constant`](args_constant.md).

```cpp
// Excerpt of the declaration inside asc::args::constant; template parameters and other members are provided by the owning class.
static constexpr decltype(Value) value() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `decltype(Value)` | Returns the compile-time constant encoded in the type. |

## Constraints

- Value is a compile-time non-type template argument; value returns the constant and does not store or read deferred pointers.

- Uses C++17 and is available in Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/argument>

bool example()
{
    static_assert(asc::args::constant<7>::value() == 7);
    return true;
}
```

## Related APIs

- [`asc::args::constant`](args_constant.md)
- [API list for this header](asc_argument.md)
