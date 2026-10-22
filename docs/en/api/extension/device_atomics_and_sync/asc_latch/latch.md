# asc::latch

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

Header: `<asc/latch>`.

`asc::latch` provides a thread synchronization object with a one-shot countdown that permanently releases waiters once the count reaches zero.

## Declaration

```cpp
namespace asc {
template<asc::memory_scope Scope> class latch;
} // namespace asc
```

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following snippet is compiled for AI Core SIMT programming. The latch is located in initialized shared GM storage; the expected count equals the number of participating threads, and each participant calls it once. After the count reaches zero, it cannot be reset for reuse.

```cpp
#include <asc/latch>

__aicore__ void example(asc::latch<asc::memory_scope::block>& latch)
{
    latch.arrive_and_wait();
}
```

## Related APIs

- [API list for this header](asc_latch.md)
