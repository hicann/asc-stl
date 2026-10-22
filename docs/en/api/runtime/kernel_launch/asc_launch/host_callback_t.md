# asc::host_callback_t

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

Header: `<asc/launch>`.

`asc::host_callback_t` is the Host callback function pointer type; the callback receives the caller-provided `void*` user data and returns no value.

## Declaration

```cpp
namespace asc {
using host_callback_t = void (*)(void*);
}  // namespace asc
```

## Constraints

- The callback signature is `void(void*)`, and the user data is managed by the caller; for the lifetime and non-throwing requirements after asynchronous submission, see `host_callback`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/launch>

bool example()
{
    int result = 0;
    asc::host_callback_t callback = [](void* data) { *static_cast<int*>(data) = 7; };
    // This directly demonstrates the callback signature; for asynchronous submission see host_callback.
    callback(&result);
    return result == 7;
}
```

## Related APIs

- [API list for this header](asc_launch.md)
