# asc::latch::count_down

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

`asc::latch::count_down` decrements the latch count by the specified amount without waiting for it to reach zero.

## Function Prototype

Member of: [`asc::latch`](latch.md).

```cpp
// Excerpt of the declaration inside the asc::latch class; template parameters and other members are provided by the owning class.
void count_down(asc::std::ptrdiff_t update = 1) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `update` | Input | The amount by which the count is decremented, 1 by default; must be strictly greater than 0 and must not exceed the current count; when the count reaches 0, the function does not wait. |

## Return Value

No return value.

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/latch>

__aicore__ void example(asc::latch<asc::memory_scope::block>* gm_latch)
{
    // The object is located in GM; blocking operations are called only when all participants can make progress concurrently.
    gm_latch->count_down();
}
```

## Related APIs

- [`asc::latch`](latch.md)
- [API list for this header](asc_latch.md)
