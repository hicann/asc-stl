# asc::std::set::size

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

Header: `<asc/std/set>`.

`asc::std::set::size` returns the number of elements in the current object.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `set`](https://en.cppreference.com/w/cpp/header/set).

## Function Prototype

Member of: [`asc::std::set`](set.md).

```cpp
// Excerpt of the declaration inside class asc::std::set; template parameters and other members are provided by the owning class.
size_type size() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `size_type` | Returns the number of elements in the current object. |

## Constraints

- In Host and AI Core SIMT programming, set<Key,Compare,A> uses an explicit GM arena.
- Construction from an allocator and from Compare+allocator.
- empty/size/begin/end/insert/find/count/clear.
- AVL balancing with a logarithmic-time insertion/lookup core.
- Duplicate-key rejection, ordered iteration, move, and destruction.
- Only the domain where capacity is sufficient and keys/comparators/allocators do not throw.
- Host and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>
#include <functional>
#include <asc/std/set>

bool example()
{
    alignas(64) unsigned char storage[16384] = {};
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::std::set<int, ::std::less<int>, asc::arena_allocator<int>> values(asc::arena_allocator<int>{arena});
    values.insert(1);
    values.insert(3);
    values.insert(3);
    return values.size() == 2;
}
```

## Related APIs

- [`asc::std::set`](set.md)
- [API list for this header](asc_std_set.md)
