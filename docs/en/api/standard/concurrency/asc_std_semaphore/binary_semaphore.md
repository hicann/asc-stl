# asc::std::binary_semaphore

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

Header: `<asc/std/semaphore>`.

`asc::std::binary_semaphore` provides an alias of a counting semaphore whose maximum permit count is one.

This interface is available on the Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `semaphore`](https://en.cppreference.com/w/cpp/header/semaphore).

## Declaration

```cpp
namespace asc::std {
using binary_semaphore = counting_semaphore<1>;
} // namespace asc::std
```

## Constraints

- Host objects use native ordinary memory and CPU atomic operations and do not manage NPU GM state. AI Core SIMT shared objects must be located in GM and must be initialized before concurrent access; calls in AI Core SIMD programming are not supported.
- All participants must be able to make progress concurrently, and operations that wait additionally require that the completion condition can be satisfied.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/semaphore>

bool example()
{
    asc::std::binary_semaphore permits(0);
    if (permits.try_acquire()) return false;
    permits.release();
    return permits.try_acquire() && !permits.try_acquire();
}
```

## Related APIs

- [API list for this header](asc_std_semaphore.md)
