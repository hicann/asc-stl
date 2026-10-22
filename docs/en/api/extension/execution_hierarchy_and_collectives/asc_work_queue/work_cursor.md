# asc::work_cursor

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

`asc::work_cursor` is the public alias of the caller-managed work cursor type; it records the next index to acquire, the end index, and the acquisition granularity. A queue reference borrowing it is created through [`make_work_queue`](make_work_queue.md).

## Declaration

After including `<asc/work_queue>`, the type name `asc::work_cursor` can be used directly. Its concrete type is provided by the library; no implementation header needs to be included.

## Parameters

Default construction initializes `next` and `end` to 0 and `grain_size` to 1. The three-argument constructor receives the start index, the end index, and the granularity in order; all parameters are 64-bit unsigned integers, and a granularity of 0 is treated as 1.

| Public field | Description |
| --- | --- |
| `next` | The next index to acquire; advanced atomically during concurrent acquisition. |
| `end` | The end index, not included in the acquirable range. |
| `grain_size` | The number of elements requested per acquisition. |

## Constraints

- The cursor is owned by the caller; it must remain valid until all queues borrowing it and all acquisition operations have finished.
- For concurrent acquisition on the device, the cursor must be located in GM commonly accessible to the participants and must be initialized before concurrent access.
- These fields must not be modified with ordinary reads and writes during concurrency; the range upper bound and granularity of the queue are determined by the values used when the queue was created.
- The index and granularity must satisfy the range and arithmetic constraints of [`acquire_work`](acquire_work.md).

## Example

The following Host example verifies the construction of the public type, the queue borrowing, and the range of the first acquisition.

```cpp
#include <asc/work_queue>

bool example()
{
    asc::work_cursor cursor{0, 20, 7};
    auto queue = asc::make_work_queue<unsigned>(cursor, 20u, 7u);
    asc::work_chunk<unsigned> chunk;
    return queue.cursor() == &cursor && asc::acquire_work(queue, chunk) &&
        chunk.begin == 0 && chunk.end == 7;
}
```

## Related APIs

- [Creating a work queue](make_work_queue.md)
- [Acquiring a work range](acquire_work.md)
- [API list for this header](asc_work_queue.md)
