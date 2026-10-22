# asc::std::insert_iterator::container_type

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

`asc::std::insert_iterator::container_type` identifies the underlying container type used by the container adaptor.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Member of: [`asc::std::insert_iterator`](insert_iterator.md).

```cpp
// Excerpt of the declaration inside asc::std::insert_iterator; template parameters and other members are provided by the enclosing class.
using container_type = Container;
```

## Constraints

- The target container must support the corresponding `insert(position, value)` operation; the insert iterator stores the container's address and does not own the container.
- The container must remain valid while the adaptor is in use; insertion operations must also follow the target container's own iterator invalidation rules.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <vector>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::insert_iterator<::std::vector<int>>::container_type;
    static_assert(asc::std::is_same_v<selected, ::std::vector<int>>);
    return true;
}
```

## Related APIs

- [`asc::std::insert_iterator`](insert_iterator.md)
- [API list for this header](asc_std_iterator.md)
