# asc::std::destroying_delete_t

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

`asc::std::destroying_delete_t` provides an empty tag type that can be used for ordinary overload selection. Starting from C++17, both the tag type and the corresponding object `asc::std::destroying_delete` are available.

Standard semantics reference: [cppreference `new`](https://en.cppreference.com/w/cpp/header/new).

## Declaration

```cpp
namespace asc::std {
struct destroying_delete_t;
} // namespace asc::std
```

## Constraints

- The declaration of the tag performs no object destruction or memory release.
- The compiler's destroying delete mechanism is governed by language and Host standard type rules; this library's tag does not add that language mechanism to C++17 and does not promise to replace the Host standard types required by the compiler.

## Example

The following example checks the type of the public tag and the corresponding object; it can be used in both C++17 and C++20.

```cpp
#include <asc/std/new>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::destroying_delete_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::destroying_delete), const asc::std::destroying_delete_t>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_new.md)
