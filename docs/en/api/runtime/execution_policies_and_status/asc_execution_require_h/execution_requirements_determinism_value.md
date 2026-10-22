# asc::execution_requirements::determinism_value

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

Header: `<asc/execution.require.h>`.

`asc::execution_requirements::determinism_value` returns the determinism requirement in the current combination.

This interface is available on Host.

## Function Prototype

Member of: [`asc::execution_requirements`](execution_requirements.md).

```cpp
// Excerpt of the declaration inside asc::execution_requirements; template parameters and other members are provided by the enclosing class.
constexpr asc::determinism determinism_value() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::determinism` | Returns the determinism requirement in the current combination. |

## Constraints

- The object is an immutable value.
- Defaults to determinism::not_guaranteed, output_ordering::unsorted, and tie_break::unspecified.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/execution.require.h>

bool example()
{
    asc::execution_requirements requirements;
    return requirements.determinism_value() == asc::determinism::not_guaranteed
        && requirements.output_ordering_value() == asc::output_ordering::unsorted
        && requirements.tie_break_value() == asc::tie_break::unspecified;
}
```

## Related APIs

- [`asc::execution_requirements`](execution_requirements.md)
- [API list for this header](asc_execution_require_h.md)
