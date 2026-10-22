# asc::std::common_iterator

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

`asc::std::common_iterator` adapts the traversal, counting, reversing, moving, or insertion behavior of the underlying iterator.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
template<class Iter, class Sent> class common_iterator;
} // namespace asc::std
```

## Constraints

- `Iter` and `Sent` are distinct types and must satisfy the pairing requirements of input/output iterators and sentinels; the adaptor stores one of the two states.
- Dereference, arrow access, and increment can only act on an object that currently holds an iterator for which the operation is valid, not on the sentinel state.
- The adaptor does not own the underlying range; the pointed-to objects must remain valid during access.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using It = asc::std::counted_iterator<int*>;
    using Common = asc::std::common_iterator<It, asc::std::default_sentinel_t>;
    Common iterator(It(values, 3));
    Common last(asc::std::default_sentinel);
    int sum = 0;
    for (; iterator != last; ++iterator) sum += *iterator;
    return sum == 12;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
