# asc::std::nothrow_t

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

`asc::std::nothrow_t` marks the allocation form that does not throw on allocation failure.

Standard semantics reference: [cppreference `new`](https://en.cppreference.com/w/cpp/header/new).

## Declaration

```cpp
namespace asc::std {
struct nothrow_t;
} // namespace asc::std
```

## Constraints

- Provides placement object lifetime interfaces and interfaces without dynamic allocation.

## Example

This tag is for overloads that accept the ASC-STL tag types; it must not be passed directly to new expressions that accept only the system std::nothrow_t.

```cpp
#include <asc/std/new>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::nothrow_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::nothrow), const asc::std::nothrow_t>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_new.md)
