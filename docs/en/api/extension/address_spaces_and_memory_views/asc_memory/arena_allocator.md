# asc::arena_allocator

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

Header: `<asc/memory>`.

`asc::arena_allocator<T>` adapts a `monotonic_arena` into an element allocator; allocations are aligned to `alignof(T)`, and a single `deallocate` does not reclaim space.

`monotonic_arena` allocates forward only, in order of arrival, on centrally managed storage; `reset()` only resets the allocation position—it neither destroys objects nor frees the underlying storage; the arena does not own the underlying storage, and its destructor does not free it. The caller is responsible for destroying objects and releasing the storage, and a single `deallocate` does not reclaim space. See [asc::monotonic_arena](monotonic_arena.md) for details.

## Declaration

```cpp
namespace asc {
template <class T>
class arena_allocator;
}  // namespace asc
```

## Constraints

- This is a lightweight allocator bound to an arena; it does not fully implement the standard named Allocator requirements, and having same-named allocate/deallocate alone does not make it usable with arbitrary standard containers.
- The arena and its storage must cover the allocator and all borrowed allocations; reset invalidates previous allocations, and deallocate does not reclaim them one by one.

- The allocator references the monotonic_arena non-owningly; the arena must remain valid while the allocator and its allocation results are in use.
- The element count multiplied by sizeof(T) must not overflow.
- allocate returns a null pointer when space is insufficient.

## Example

The following Host example constructs four integers in caller-provided storage and ends the object lifetimes before resetting the arena.

```cpp
#include <asc/memory>
#include <asc/std/memory>

bool use_arena_allocator()
{
    alignas(int) unsigned char storage[128];
    asc::monotonic_arena arena(storage, sizeof(storage));
    asc::arena_allocator<int> allocator(arena);
    int* values = allocator.allocate(4);
    if (values == nullptr) {
        return false;
    }
    for (int i = 0; i < 4; ++i) {
        asc::std::construct_at(values + i, i + 1);
    }
    const bool ok = values[0] == 1 && values[3] == 4;
    asc::std::destroy_n(values, 4);
    allocator.deallocate(values, 4);
    arena.reset();
    // reset only allows the storage to be reused; the lifetime of storage is managed by this function.
    return ok && arena.used() == 0;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
