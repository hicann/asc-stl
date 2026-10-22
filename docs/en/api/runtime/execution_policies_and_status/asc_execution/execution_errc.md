# asc::execution_errc

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

`asc::execution_errc` defines the common status categories of the ASC-STL Host execution interfaces, used to distinguish success, invalid arguments, insufficient temporary storage, and backend runtime errors.

## Declaration

```cpp
namespace asc {
enum class execution_errc : int;
} // namespace asc
```

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

- [API list for this header](asc_execution.md)
