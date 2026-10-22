# asc::std::unreachable_sentinel

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

Header: `<asc/std/iterator>`.

`asc::std::unreachable_sentinel` provides a sentinel object that never equals a valid iterator.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
inline constexpr const unreachable_sentinel_t unreachable_sentinel;
} // namespace asc::std
```

## Constraints

- When compared with an applicable iterator, this sentinel always indicates that the end position has not yet been reached.
- The caller must terminate traversal through other conditions and guarantee that every dereference and increment is valid; this sentinel does not check the actual boundary.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    int* iterator = values;
    return iterator != asc::std::unreachable_sentinel &&
           values + 2 != asc::std::unreachable_sentinel;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
