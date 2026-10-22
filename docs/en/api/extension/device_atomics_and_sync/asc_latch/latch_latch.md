# asc::latch::latch

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

Header: `<asc/latch>`.

`asc::latch::latch` initializes an `asc::latch` object with the arguments provided by the caller.

## Function Prototype

Member of: [`asc::latch`](latch.md).

```cpp
// Excerpt of the declaration inside the asc::latch class; template parameters and other members are provided by the owning class.
constexpr explicit latch(asc::std::ptrdiff_t expected) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `expected` | Input | The initial count value of the latch, that is, the total number of arrivals required before it opens; after the count is decremented to 0, the latch opens and stays open. |

## Return Value

No return value.

## Constraints

- The initial expected must be within `[0, max()]`; when it is 0, waits pass immediately. The update of each count_down/arrive_and_wait must be strictly greater than 0 and must not exceed the remaining count.

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/latch>

#include <asc/std/new>

__aicore__ void example(asc::latch<asc::memory_scope::block>* gm_storage)
{
    // gm_storage is caller-provided, aligned GM storage.
    ::new (static_cast<void*>(gm_storage)) asc::latch<asc::memory_scope::block>(1);
}
```

## Related APIs

- [`asc::latch`](latch.md)
- [API list for this header](asc_latch.md)
