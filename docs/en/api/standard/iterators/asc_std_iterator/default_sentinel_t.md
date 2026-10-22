# asc::std::default_sentinel_t

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

`asc::std::default_sentinel_t` identifies the corresponding iterator capability or end-sentinel category.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
struct default_sentinel_t;
} // namespace asc::std
```

## Constraints

- The default sentinel serves only as an end marker; it must be used together with iterators that define comparison operations for this sentinel, for example `counted_iterator`.
- The sentinel does not hold a range and cannot be dereferenced.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::counted_iterator<int*> iterator(values, 2);
    int sum = 0;
    for (; iterator != asc::std::default_sentinel; ++iterator) sum += *iterator;
    return sum == 6 && iterator.count() == 0;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
