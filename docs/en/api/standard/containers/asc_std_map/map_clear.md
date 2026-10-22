# asc::std::map::clear

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

Header: `<asc/std/map>`.

`asc::std::map::clear` removes all elements and leaves the container empty.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `map`](https://en.cppreference.com/w/cpp/header/map).

## Function Prototype

Member of: [`asc::std::map`](map.md).

```cpp
// Excerpt of the declaration inside class asc::std::map; template parameters and other members are provided by the owning class.
void clear() noexcept;
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- In Host and AI Core SIMT programming, map<Key,T,Compare,A> requires an explicit GM arena.
- Construction with allocator, and with Compare+allocator.
- empty/size/begin/end/insert/find/count/`operator[]`/clear.
- AVL balancing with a logarithmic insertion/lookup core.
- Duplicate keys are rejected; ordered iteration, move, and destruction.
- Only in domains with sufficient capacity and non-throwing key/value, comparison, and allocator operations.
- Host and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>
#include <functional>
#include <asc/std/map>
#include <asc/std/utility>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    using allocator = asc::arena_allocator<asc::std::pair<const int, int>>;
    asc::std::map<int, int, ::std::less<int>, allocator> values(allocator{arena});
    values[1] = 7;
    values[3] = 9;
    values.clear();
    return values.empty();
}
```

## Related APIs

- [`asc::std::map`](map.md)
- [API list for this header](asc_std_map.md)
