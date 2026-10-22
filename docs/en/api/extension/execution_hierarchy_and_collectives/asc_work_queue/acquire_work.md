# asc::acquire_work

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

`asc::acquire_work` atomically acquires a non-overlapping index range from the shared work queue and writes the range into `chunk`. Returning false means there is no remaining work.

Host, AI Core SIMD programming, and AI Core SIMT programming can each use their applicable overloads.

## Function Prototype

Host and AI Core SIMT programming can use the queue-reference form or the plain cursor-pointer form.

```cpp
namespace asc {
template<class Index>
bool acquire_work(work_queue_ref<Index> queue, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

```cpp
namespace asc {
template<class Index>
bool acquire_work(work_cursor* cursor, Index end, Index grain_size, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

AI Core SIMD programming must use the GM address-space pointer form.

```cpp
namespace asc {
template<class Index>
bool acquire_work(__gm__ work_cursor* cursor, Index end, Index grain_size, work_chunk<Index>& chunk) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | A supported 32-bit or 64-bit unsigned index type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `queue` | Input | References the concurrent work queue managed by the caller; the cursor must remain valid while work is being acquired. |
| `cursor` | Input/Output | The shared work cursor; `next` is advanced atomically during acquisition. |
| `end` | Input | The end index of the acquirable range, exclusive. |
| `grain_size` | Input | The granularity of this acquisition; 0 is treated as 1. |
| `chunk` | Output | Receives the half-open range on success; set to an empty range on failure. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when a non-empty range is acquired; returns `false` when the cursor is null or has reached the end position. |

## Constraints

- Index must be a supported 32-bit or 64-bit unsigned integer.
- The queue reference and its cursor must remain valid during concurrent acquisition.
- Adding a positive granularity to the current cursor value must be representable by a 64-bit unsigned integer; acquisition must not rely on overflow wrap-around to continue.
- This interface does not guarantee acquisition order, fairness, or implicit synchronization across threads; see [`asc::work_cursor`](work_cursor.md) for cursor construction and lifetime.

## Example

The following snippet demonstrates queue acquisition in AI Core SIMT programming; plain AI Core SIMD programming should use the global-memory cursor-pointer overload listed on this page.

```cpp
#include <asc/work_queue>

__aicore__ decltype(auto) example(asc::work_queue_ref<unsigned int> queue)
{
    asc::work_chunk<unsigned int> chunk;
    return asc::acquire_work(queue, chunk);
}
```

## Related APIs

- [API list for this header](asc_work_queue.md)
