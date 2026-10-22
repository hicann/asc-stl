# asc::make_work_queue

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

`asc::make_work_queue` combines the caller-managed work cursor, end index, and granularity into a non-owning `work_queue_ref<Index>` for use by the concurrent work acquisition interfaces.

This interface can be used for queue description on the Host and on the device; the actual acquisition operation must also satisfy the constraints of its programming mode and address space.

## Function Prototype

```cpp
namespace asc {
template <class Index>
constexpr asc::work_queue_ref<Index> make_work_queue(asc::work_cursor& cursor, Index end, Index grain_size) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Index` | The work index type: only uint32_t and uint64_t are supported. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `cursor` | Input/Output | Reference to the caller-managed GM atomic work cursor (work_cursor): this call only borrows it without taking ownership, later work acquisitions advance its next value with an atomic fetch-add; it must remain valid until no further acquisition happens. |
| `end` | Input | The upper bound of the work index (exclusive): acquired chunks are clipped to this value. |
| `grain_size` | Input | The granularity of each acquisition (the number of indices in a single chunk): it must be positive, and the cursor value plus this value must not overflow. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::work_queue_ref<Index>` | Returns a non-owning queue object referencing the caller's work cursor. |

## Constraints

- Index supports uint32_t, uint64_t, and 64-bit unsigned long long; other types are not automatically accepted just because their width matches. The Host can perform value operations and acquisition, device participants must still use a shared GM cursor, and SIMD uses the corresponding GM-qualified entry.

See [`asc::work_cursor`](work_cursor.md) for cursor construction and lifetime.

- Index must be a supported 32-bit or 64-bit unsigned integer.
- grain_size must be greater than zero.
- cursor must remain valid while the queue reference is in use.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/work_queue>

bool example()
{
    asc::work_cursor cursor{0, 20, 7};
    const auto queue = asc::make_work_queue<unsigned>(cursor, 20u, 7u);
    return queue.cursor() == &cursor && queue.end_value() == 20 && queue.grain_size() == 7;
}
```

## Related APIs

- [API list for this header](asc_work_queue.md)
