# asc::execution_status::success

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

Header: `<asc/execution>`.

`asc::execution_status::success` checks whether the common status category is `execution_errc::success`.

## Function Prototype

Member of: [`asc::execution_status`](execution_status.md).

```cpp
// Excerpt of the declaration inside asc::execution_status; template parameters and other members are provided by the enclosing class.
constexpr bool success() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Can only be used on the Host.
- Status values are trivially copyable.
- For a success status, code() is execution_errc::success and native_code() is 0; a failure status retains a status code that can be used for diagnosis.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/execution>

bool example()
{
    asc::execution_status success;
    asc::execution_status failure(asc::execution_errc::backend_error, 17);
    return success.success() && success.code() == asc::execution_errc::success && success.native_code() == 0
        && !failure.success() && failure.code() == asc::execution_errc::backend_error && failure.native_code() == 17;
}
```

## Related APIs

- [`asc::execution_status`](execution_status.md): Argument validation and task submission status; a successful submission does not mean the asynchronous work has completed.
