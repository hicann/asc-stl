# asc::std::terminate

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

Header: `<asc/std/exception>`.

`asc::std::terminate` terminates the current execution and does not return. On Host it calls the currently installed standard termination handler; on the device side it ends the current device execution.

Standard semantics reference: [cppreference `exception`](https://en.cppreference.com/w/cpp/header/exception).

## Function Prototype

```cpp
namespace asc::std {
void terminate() noexcept;
} // namespace asc::std
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Does not return after the call.
- On Host, calls the currently installed standard termination handler.
- In AI Core SIMD and AI Core SIMT programming, terminates the current device execution. The specific status code of a device fault is not part of the interface guarantee.

## Example

The following code is for BiSheng ASC translation units and shows the call on the Host submission side and in an AI Core device function, respectively.

```cpp
#include <asc/std/exception>
#include <cstdio>
#include <cstdlib>
#include <exception>

#if defined(__CCE__) || defined(__NPU_COMPILER_INTERNAL_PURE_SIMT__)
__aicore__ void device_example()
{
    asc::std::terminate();
}
#else
int main()
{
    ::std::set_terminate([] {
        ::std::puts("ASC_STL_TERMINATE_HANDLER_PASS");
        ::std::fflush(stdout);
        ::std::_Exit(42);
    });
    asc::std::terminate();
}
#endif
```

## Related APIs

- [API list for this header](asc_std_exception.md)
