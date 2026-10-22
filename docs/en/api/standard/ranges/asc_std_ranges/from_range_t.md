# asc::std::from_range_t

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

Header: `<asc/std/ranges>`.

`asc::std::from_range_t` is an empty tag type identifying the "construct from range" overload; the corresponding constant is `asc::std::from_range`. It does not denote a dangling result, and it does not store or take ownership of a range.

## Declaration

```cpp
namespace asc::std {
struct from_range_t;
} // namespace asc::std
```

## Constraints

- Serves only as a tag for constructor or function overloads; whether a specific type has a constructor accepting this tag must be checked in that type's interface.
- The construction tag does not start traversal, does not store element addresses, and does not extend the range's lifetime.

## Example

`from_range_t` is the marker type that distinguishes the construct-from-range overload. The following checks the type of the public marker object; whether a container supports this overload is governed by the corresponding container prototype.

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_empty_v<asc::std::from_range_t>);
    static_assert(asc::std::is_same_v<decltype(asc::std::from_range), const asc::std::from_range_t>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
