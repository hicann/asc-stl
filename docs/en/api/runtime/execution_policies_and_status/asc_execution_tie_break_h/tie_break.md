# asc::tie_break

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

Header: `<asc/execution.tie_break.h>`.

`asc::tie_break` specifies the index selection rule applied when multiple positions satisfy the selection condition at the same time.

This interface is available on Host.

## Declaration

```cpp
namespace asc {
enum class tie_break;
}  // namespace asc
```

## Constraints

- The current parallel extremum frontend does not yet apply non-default index preferences; storing this property does not guarantee that equal extrema are selected by the smaller or larger index. When this rule is needed, the caller must handle equal elements explicitly.

- Only three values are provided.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/execution.require.h>

bool example()
{
    auto requirements = asc::require(asc::tie_break::unspecified);
    return requirements.tie_break_value() == asc::tie_break::unspecified;
}
```

## Related APIs

- [API list for this header](asc_execution_tie_break_h.md)
