# asc::work_queue_ref

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

Header: `<asc/work_queue>`.

`asc::work_queue_ref<Index>` non-owningly references the caller-managed GM atomic cursor and stores the task end position and the granularity of each acquisition by value.

This interface is available in AI Core SIMD programming and AI Core SIMT programming.

## Declaration

```cpp
namespace asc {
template<class Index> class work_queue_ref;
} // namespace asc
```

## Constraints

It borrows [`asc::work_cursor`](work_cursor.md) at construction and does not take ownership of the cursor.

- Index must be a supported 32-bit or 64-bit unsigned integer.
- The cursor must be located in available GM and remain valid until all concurrent acquisitions complete.
- A non-positive granularity is stored as 1.
- The end of an acquired range does not exceed `end`; the cursor plus the granularity must be representable by a 64-bit unsigned integer, and overflow wrap-around must not be relied upon.
- The interface does not guarantee acquisition order or fairness.

## Example

Default construction yields an empty queue reference; acquiring from an empty reference returns false and clears the output range. Actual concurrent acquisition must first bind a valid GM cursor.

```cpp
#include <asc/work_queue>
#include <asc/std/cstdint>

bool example()
{
    asc::work_queue_ref<asc::std::uint32_t> queue;
    asc::work_chunk<asc::std::uint32_t> chunk(2U, 5U);
    const bool acquired = asc::acquire_work(queue, chunk);
    return queue.cursor() == nullptr && queue.grain_size() == 1 && !acquired && chunk.empty();
}
```

## Related APIs

- [API list for this header](asc_work_queue.md)
