# asc::monotonic_arena

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

`asc::monotonic_arena` allocates memory forward only, honoring alignment requirements, in contiguous caller-provided storage. A single allocation cannot be freed; `reset()` makes the entire capacity reusable at once.

## Declaration

```cpp
namespace asc {
class monotonic_arena;
} // namespace asc
```

## Constraints

- The underlying storage is owned by the caller and must remain valid while the arena is in use.
- `alignment` must be a non-negative integer power of two, i.e., values such as 1, 2, 4, and 8.
- allocate returns a null pointer when space is insufficient.
- Allocations obtained before a reset must not be used afterwards.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/memory>

bool example()
{
    alignas(16) unsigned char storage[64]{};
    asc::monotonic_arena arena(storage, sizeof(storage));
    void* first = arena.allocate(16, 16);
    void* second = arena.allocate(16, 16);
    return first == storage && second == storage + 16;
}
```

## Related APIs

- [API list for this header](asc_memory.md)
