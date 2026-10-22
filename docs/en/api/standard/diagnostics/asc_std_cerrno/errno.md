# errno

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

Header: `<asc/std/cerrno>`.

`errno` is a modifiable int lvalue macro on Host, used to read the error code specified by C-compatible interfaces; when to read it should be determined by the conventions of the specific interface, and a successful call does not guarantee it is cleared to zero. The device side does not provide errno state.

## Declaration

Host obtains the errno macro of the platform `<cerrno>` through the public header; the concrete expansion is decided by the platform, and ASC-STL does not define an extra function for obtaining the errno address.

```cpp
#include <asc/std/cerrno>
```

## Constraints

- errno state can only be used on Host; it is managed by the platform C library and is usually thread-local state.
- The device side provides only the three error code constants EDOM, EILSEQ, and ERANGE, and does not provide the errno object.
- Interpret the error code only when the failure condition agreed by the specific C interface holds; when older errors need to be distinguished, the caller clears it to zero first.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/cerrno>

bool example()
{
    const int saved = errno;
    errno = 0;
    const bool cleared = errno == 0;
    errno = saved;
    return cleared;
}
```

## Related APIs

- [API list for this header](asc_std_cerrno.md)
