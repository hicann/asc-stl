# asc::std::align_val_t

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

Header: `<asc/std/new>`.

`asc::std::align_val_t` passes extended alignment values to placement object lifetime interfaces.

Standard semantics reference: [cppreference `new`](https://en.cppreference.com/w/cpp/header/new).

## Declaration

The underlying type is the size_t type provided by the compiler; this is a scoped enum of ASC-STL itself.

```cpp
namespace asc::std {
enum class align_val_t : __SIZE_TYPE__ {};
}
```

## Constraints

- Provides placement object lifetime interfaces and interfaces without dynamic allocation.

## Example

This enum carries the alignment in bytes; the value must be a power of two. It is a different type from the system std::align_val_t and must not be passed directly to the system's aligned new overloads.

```cpp
#include <asc/std/new>
#include <asc/std/cstddef>

bool example()
{
    constexpr asc::std::align_val_t alignment{64};
    static_assert(static_cast<asc::std::size_t>(alignment) == 64);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_new.md)
