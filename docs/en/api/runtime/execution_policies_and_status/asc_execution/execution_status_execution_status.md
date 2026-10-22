# asc::execution_status::execution_status

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

The default constructor creates a success status; the parameterized constructor creates the specified status and retains the passed-in native status code only when the status category is `backend_error`.

## Function Prototype

Member of: [`asc::execution_status`](execution_status.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::execution_status; template parameters and other members are provided by the enclosing class.
constexpr execution_status() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::execution_status; template parameters and other members are provided by the enclosing class.
constexpr explicit execution_status(asc::execution_errc code, int native_code = 0) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `code` | Input | The error or execution status category to store or query. |
| `native_code` | Input | The native status code returned by the underlying runtime; meaningful only for the corresponding error category. |

## Return Value

No return value.

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
