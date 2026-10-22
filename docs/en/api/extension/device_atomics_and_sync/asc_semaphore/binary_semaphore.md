# asc::binary_semaphore

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

`asc::binary_semaphore` is an alias of counting_semaphore with the maximum count fixed at 1.

## Declaration

```cpp
namespace asc {
template<asc::memory_scope Scope> using binary_semaphore = asc::counting_semaphore<Scope, 1>;
} // namespace asc
```

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following snippet shows the alias type with concrete template arguments.

```cpp
#include <asc/semaphore>

__aicore__ void use_type()
{
    using selected = asc::binary_semaphore<asc::memory_scope::device>;
}
```

## Related APIs

- [API list for this header](asc_semaphore.md)
