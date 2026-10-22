# asc::std::deque::end

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

`asc::std::deque::end` returns an iterator to the one-past-the-end position.

Standard semantics reference: [cppreference `deque`](https://en.cppreference.com/w/cpp/header/deque).

## Function Prototype

Member of: [`asc::std::deque`](deque.md).

```cpp
// Excerpt of the declaration inside class asc::std::deque; template parameters and other members are provided by the owning class.
iterator end() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `iterator` | Returns an iterator to the one-past-the-end position. |

## Constraints

- Explicit-allocator construction of deque<T,A>.
- push/emplace/pop_front/back within a bounded block map.
- empty/size/front/back/`operator[]` and the random-access iteration core.
- References to existing elements remain stable when a new end block is allocated.
- clear/destruction.
- Only the domains where capacity is sufficient and exceptions are not thrown.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>
#include <asc/std/deque>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::deque<int, asc::arena_allocator<int>> values(asc::arena_allocator<int>{arena});
    values.push_back(1);
    values.push_back(3);
    auto last = values.end();
    auto current = values.begin();
    unsigned int count = 0;
    for (; current != last; ++current) ++count;
    return count == 2;
}
```

## Related APIs

- [`asc::std::deque`](deque.md)
- [API list for this header](asc_std_deque.md)
