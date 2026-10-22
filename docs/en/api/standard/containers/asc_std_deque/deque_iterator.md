# asc::std::deque::iterator

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

Header: `<asc/std/deque>`.

`asc::std::deque::iterator` is the iterator type for traversing the elements of the corresponding container.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Declaration

Member of: [`asc::std::deque`](deque.md).

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
class iterator;
```

## Constraints

- Explicit-allocator construction of deque<T,A>.
- push/emplace/pop_front/back within a bounded block map.
- empty/size/front/back/`operator[]` and the random-access iteration core.
- References to existing elements remain stable when a new end block is allocated.
- clear/destruction.
- Only the domains where capacity is sufficient and exceptions are not thrown.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/memory>
#include <asc/std/deque>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    using Container = asc::std::deque<int, asc::arena_allocator<int>>;
    Container values(asc::arena_allocator<int>{arena});
    values.push_back(2);
    values.push_back(4);
    auto it = values.begin();
    *it = 7;
    return values.front() == 7 && *++it == 4;
}
```

## Related APIs

- [`asc::std::deque`](deque.md)
- [API list for this header](asc_std_deque.md)
