# asc::counting_semaphore

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

Header: `<asc/semaphore>`.

`asc::counting_semaphore` maintains a counting semaphore that supports concurrent acquire and release.

## Declaration

```cpp
namespace asc {
template<asc::memory_scope Scope, asc::std::ptrdiff_t LeastMaxValue = 2147483647> class counting_semaphore;
} // namespace asc
```

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following snippet is compiled for AI Core SIMT programming. permits is a semaphore already constructed in GM, with the initial permit count within [0, 2]; the example returns the permit after acquiring it successfully.

```cpp
#include <asc/semaphore>

__aicore__ bool example(asc::counting_semaphore<asc::memory_scope::device, 2>& permits)
{
    if (!permits.try_acquire()) return false;
    // Access the resource protected by the permit here.
    permits.release();
    return true;
}
```

## Related APIs

- [API list for this header](asc_semaphore.md)
