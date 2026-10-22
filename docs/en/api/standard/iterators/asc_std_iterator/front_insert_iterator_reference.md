# asc::std::front_insert_iterator::reference

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

`asc::std::front_insert_iterator::reference` identifies the writable element reference type.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Member of: [`asc::std::front_insert_iterator`](front_insert_iterator.md).

```cpp
// Excerpt of the declaration inside asc::std::front_insert_iterator; template parameters and other members are provided by the enclosing class.
using reference = void;
```

## Constraints

- The target container must support the corresponding `push_front(value)` operation; the insert iterator stores the container's address and does not own the container.
- The container must remain valid while the adaptor is in use; insertion operations must also follow the target container's own iterator invalidation rules.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <deque>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::front_insert_iterator<::std::deque<int>>::reference;
    static_assert(asc::std::is_same_v<selected, void>);
    return true;
}
```

## Related APIs

- [`asc::std::front_insert_iterator`](front_insert_iterator.md)
- [API list for this header](asc_std_iterator.md)
