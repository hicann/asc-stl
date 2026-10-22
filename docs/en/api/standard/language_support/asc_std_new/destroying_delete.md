# asc::std::destroying_delete

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

`asc::std::destroying_delete` is a constant object of type `destroying_delete_t` that, starting from C++17, can be used as a tag argument for ordinary overloads.

## Declaration

```cpp
namespace asc::std {
inline constexpr destroying_delete_t destroying_delete{};
} // namespace asc::std
```

## Constraints

- The object itself holds no resources and performs no destruction or release operations.
- This vocabulary type does not change the compiler's delete expressions or destroying delete rules.

## Example

The following example uses a tag parameter of an ordinary function and does not rely on destroying delete syntax.

```cpp
#include <asc/std/new>

constexpr bool selected(asc::std::destroying_delete_t) { return true; }
static_assert(selected(asc::std::destroying_delete));
```

## Related APIs

- [`asc::std::destroying_delete_t`](destroying_delete_t.md)
- [API list for this header](asc_std_new.md)
