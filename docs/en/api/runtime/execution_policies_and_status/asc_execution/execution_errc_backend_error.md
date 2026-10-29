# asc::execution_errc::backend_error

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

`asc::execution_errc::backend_error` indicates that the underlying runtime call failed; the native status code returned by the backend can be obtained through `execution_status::native_code()`.

## Declaration

Member of: [`asc::execution_errc`](execution_errc.md).

```cpp
// Excerpt of the declaration inside asc::execution_errc; template parameters and other members are provided by the enclosing class.
backend_error = 3;
```

## Constraints

- Can only be used on the Host.
- Status values are trivially copyable.
- For a success status, code() is execution_errc::success and native_code() is 0; a failure status retains a status code that can be used for diagnosis.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/execution>

constexpr auto value = asc::execution_errc::backend_error;
static_assert(value != asc::execution_errc::success, "documented states are distinct");
static_assert(value != asc::execution_errc::invalid_argument, "documented states are distinct");
static_assert(value != asc::execution_errc::insufficient_storage, "documented states are distinct");
```

## Related APIs

- [`asc::execution_errc`](execution_errc.md)
- [API list for this header](asc_execution.md)
