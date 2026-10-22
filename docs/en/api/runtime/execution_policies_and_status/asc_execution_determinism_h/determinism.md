# asc::determinism

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

Header: `<asc/execution.determinism.h>`.

`asc::determinism` specifies the level of guarantee that a parallel algorithm produces repeatable results for identical inputs.

This interface is available on Host.

## Declaration

```cpp
namespace asc {
enum class determinism;
} // namespace asc
```

## Constraints

- Only three values are provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/execution.require.h>

bool example()
{
    auto requirements = asc::require(asc::determinism::not_guaranteed);
    return requirements.determinism_value() == asc::determinism::not_guaranteed;
}
```

## Related APIs

- [API list for this header](asc_execution_determinism_h.md)
